import { ApplicationModel } from './ApplicationModel.js';
// import { StorageManager } from './StorageManager.js'; 

class ApplicationUI {
  constructor() {
    this.app = new ApplicationModel();
    this.usuarioActual = null;
  }

  async iniciar() {
    await this._cargarUsuariosDesdeIndexedDB();

    let user = prompt("Usuario:");
    let pass = prompt("Contraseña:");
    this.usuarioActual = this.app.usuarios.verificarCredenciales(user, pass);

    if (this.usuarioActual) {
      alert("Bienvenido, " + this.usuarioActual.usuario);
      this.menuPrincipal();
    } else {
      alert("Credenciales incorrectas.");
    }
  }

  async _cargarUsuariosDesdeIndexedDB() {
    const db = await this._abrirDB();
    const usuarios = await this._obtenerUsuariosDesdeIndexedDB(db);

    if (usuarios.length === 0) {
      await this._guardarUsuariosEnIndexedDB(db, this.app.usuarios.usuarios);
      this.usuariosIndexed = this.app.usuarios.usuarios;
    } else {
      this.app.usuarios.usuarios = usuarios;
    }
  }

  async _abrirDB() {
    return new Promise((resolve, reject) => {
      const request = indexedDB.open('MiApp', 1);

      request.onupgradeneeded = (event) => {
        const db = event.target.result;
        if (!db.objectStoreNames.contains('usuarios')) {
          db.createObjectStore('usuarios', { keyPath: 'usuario' });
        }
      };

      request.onsuccess = (event) => resolve(event.target.result);
      request.onerror = (event) => reject(event.target.error);
    });
  }

  async _obtenerUsuariosDesdeIndexedDB(db) {
    return new Promise((resolve, reject) => {
      const tx = db.transaction(['usuarios'], 'readonly');
      const store = tx.objectStore('usuarios');
      const request = store.getAll();

      request.onsuccess = () => resolve(request.result);
      request.onerror = (e) => reject(e);
    });
  }

  async _guardarUsuariosEnIndexedDB(db, usuarios) {
    return new Promise((resolve, reject) => {
      const tx = db.transaction(['usuarios'], 'readwrite');
      const store = tx.objectStore('usuarios');
      usuarios.forEach(u => store.add(u));
      tx.oncomplete = () => resolve();
      tx.onerror = (e) => reject(e);
    });
  }

  menuPrincipal() {
    const tipo = this.usuarioActual.tipo;
    const Tipos = this.app.usuarios.TipoUsuario;

    const opcionesBase = ["1. Cambiar contraseña", "2. Ver artículos"];

    const opcionesPorTipo = {
      [Tipos.ADMINISTRADOR]: ["3. Agregar artículo", "4. Editar artículo", "5. Eliminar artículo", "6. Ver usuarios"],
      [Tipos.VENDEDOR]: ["3. Agregar artículo", "4. Editar artículo", "5. Comprar artículo"],
      [Tipos.DEPOSITO]: ["3. Agregar artículo", "4. Editar artículo"],
      [Tipos.CLIENTE]: ["3. Comprar artículo"]
    };

    const opciones = opcionesBase.concat(opcionesPorTipo[tipo] || []);
    const opcion = parseInt(prompt("Menú Principal:\n" + opciones.join("\n")));
    this.ejecutarOpcion(opcion);
  }

  ejecutarOpcion(opcion) {
    const Tipos = this.app.usuarios.TipoUsuario;
    const tipo = this.usuarioActual.tipo;

    switch (opcion) {
      case 1:
        this._cambiarContrasena();
        break;

      case 2:
        this._mostrarListaArticulos();
        break;

      case 3:
        if ([Tipos.ADMINISTRADOR, Tipos.VENDEDOR, Tipos.DEPOSITO].includes(tipo)) {
          this._agregarArticulo();
        } else if (tipo === Tipos.CLIENTE) {
          this._comprarArticulo();
        }
        break;

      case 4:
        if ([Tipos.ADMINISTRADOR, Tipos.VENDEDOR, Tipos.DEPOSITO].includes(tipo)) {
          this._editarArticulo();
        }
        break;

      case 5:
        if (tipo === Tipos.ADMINISTRADOR) {
          this._eliminarArticulo();
        } else if (tipo === Tipos.VENDEDOR) {
          this._comprarArticulo();
        }
        break;

      case 6:
        if (tipo === Tipos.ADMINISTRADOR) {
          this._mostrarUsuarios();
        }
        break;

      default:
        alert("Opción inválida.");
    }

    this.menuPrincipal();
  }

  _cambiarContrasena() {
    let nueva = prompt("Nueva contraseña:");
    if (this.app.usuarios.cambiarContrasena(this.usuarioActual, nueva)) {
      alert("Contraseña actualizada.");
    } else {
      alert("No cumple con los requisitos.");
    }
  }

  _mostrarListaArticulos() {
    const lista = this.app.articulos.listarArticulos()
      .map(a => `${a.id} - ${a.nombre} - $${a.precio} - Stock: ${a.stock}`)
      .join("\n");
    alert(lista);
  }

  _agregarArticulo() {
    let id = parseInt(prompt("ID:"));
    let nombre = prompt("Nombre:");
    let precio = parseFloat(prompt("Precio:"));
    let stock = parseInt(prompt("Stock:"));
    this.app.articulos.agregarArticulo(id, nombre, precio, stock);
    alert("Artículo agregado.");
  }

  _editarArticulo() {
    let id = parseInt(prompt("ID del artículo a editar:"));
    let nuevoNombre = prompt("Nuevo nombre:");
    let nuevoPrecio = parseFloat(prompt("Nuevo precio:"));
    let nuevoStock = parseInt(prompt("Nuevo stock:"));
    const ok = this.app.articulos.editarArticulo(id, nuevoNombre, nuevoPrecio, nuevoStock);
    alert(ok ? "Artículo editado." : "ID no encontrado.");
  }

  _eliminarArticulo() {
    let id = parseInt(prompt("ID del artículo:"));
    const ok = this.app.articulos.eliminarArticulo(id);
    alert(ok ? "Artículo eliminado." : "ID no encontrado.");
  }

  _comprarArticulo() {
    let id = parseInt(prompt("ID del artículo:"));
    let cantidad = parseInt(prompt("Cantidad:"));
    let total = this.app.articulos.comprarArticulo(id, cantidad);
    alert(total != null ? `Total a pagar: $${total}` : "Stock insuficiente o ID inválido.");
  }

  _mostrarUsuarios() {
    const usuarios = this.app.usuarios.listarUsuarios()
      .map(u => `${u.usuario} - Tipo: ${u.tipo}`)
      .join("\n");
    alert(usuarios);
  }

  // guardarDatos() {
  //   StorageManager.guardarUsuarios(this.app.usuarios);
  //   StorageManager.guardarArticulos(this.app.articulos);
  // }
}

export { ApplicationUI };
