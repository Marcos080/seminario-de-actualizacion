import { ApplicationModel } from './ApplicationModel.js';

class ApplicationUI {
  constructor() {
    this.app = new ApplicationModel();
    this.usuarioActual = null;
  }

  iniciar() {
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

  menuPrincipal() {
    let tipo = this.usuarioActual.tipo;
    let opciones = ["1. Cambiar contraseña", "2. Ver artículos"];
    const Tipos = this.app.usuarios.TipoUsuario;

    if (tipo === Tipos.ADMINISTRADOR) {
      opciones.push("3. Agregar artículo", "4. Editar artículo", "5. Eliminar artículo", "6. Ver usuarios");
    } else if (tipo === Tipos.VENDEDOR) {
      opciones.push("3. Agregar artículo", "4. Editar artículo", "5. Comprar artículo");
    } else if (tipo === Tipos.DEPOSITO) {
      opciones.push("3. Agregar artículo", "4. Editar artículo");
    } else if (tipo === Tipos.CLIENTE) {
      opciones.push("3. Comprar artículo");
    }

    let opcion = parseInt(prompt("Menú Principal:\n" + opciones.join("\n")));
    this.ejecutarOpcion(opcion);
  }

  ejecutarOpcion(opcion) {
    const Tipos = this.app.usuarios.TipoUsuario;
    const tipo = this.usuarioActual.tipo;

    switch (opcion) {
      case 1:
        let nueva = prompt("Nueva contraseña:");
        if (this.app.usuarios.cambiarContrasena(this.usuarioActual, nueva)) {
          alert("Contraseña actualizada.");
        } else {
          alert("No cumple con los requisitos.");
        }
        break;

      case 2:
        const lista = this.app.articulos.listarArticulos()
          .map(a => `${a.id} - ${a.nombre} - $${a.precio} - Stock: ${a.stock}`)
          .join("\n");
        alert(lista);
        break;

      case 3:
        if ([Tipos.ADMINISTRADOR, Tipos.VENDEDOR, Tipos.DEPOSITO].includes(tipo)) {
          let id = parseInt(prompt("ID:"));
          let nombre = prompt("Nombre:");
          let precio = parseFloat(prompt("Precio:"));
          let stock = parseInt(prompt("Stock:"));
          this.app.articulos.agregarArticulo(id, nombre, precio, stock);
          alert("Artículo agregado.");
        } else if (tipo === Tipos.CLIENTE) {
          let id = parseInt(prompt("ID del artículo:"));
          let cantidad = parseInt(prompt("Cantidad:"));
          let total = this.app.articulos.comprarArticulo(id, cantidad);
          alert(total != null ? `Total a pagar: $${total}` : "Stock insuficiente o ID inválido.");
        }
        break;

      case 4:
        if ([Tipos.ADMINISTRADOR, Tipos.VENDEDOR, Tipos.DEPOSITO].includes(tipo)) {
          let id = parseInt(prompt("ID del artículo a editar:"));
          let nuevoNombre = prompt("Nuevo nombre:");
          let nuevoPrecio = parseFloat(prompt("Nuevo precio:"));
          let nuevoStock = parseInt(prompt("Nuevo stock:"));
          const ok = this.app.articulos.editarArticulo(id, nuevoNombre, nuevoPrecio, nuevoStock);
          alert(ok ? "Artículo editado." : "ID no encontrado.");
        }
        break;

      case 5:
        if ([Tipos.ADMINISTRADOR, Tipos.VENDEDOR].includes(tipo)) {
          let id = parseInt(prompt("ID del artículo:"));
          if (tipo === Tipos.ADMINISTRADOR) {
            const ok = this.app.articulos.eliminarArticulo(id);
            alert(ok ? "Artículo eliminado." : "ID no encontrado.");
          } else {
            let cantidad = parseInt(prompt("Cantidad:"));
            let total = this.app.articulos.comprarArticulo(id, cantidad);
            alert(total != null ? `Total a pagar: $${total}` : "Stock insuficiente o ID inválido.");
          }
        }
        break;

      case 6:
        if (tipo === Tipos.ADMINISTRADOR) {
          const usuarios = this.app.usuarios.listarUsuarios()
            .map(u => `${u.usuario} - Tipo: ${u.tipo}`)
            .join("\n");
          alert(usuarios);
        }
        break;

      default:
        alert("Opción inválida.");
    }

    this.menuPrincipal(); 
  }
}

export { ApplicationUI };
