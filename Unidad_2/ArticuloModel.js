class ArticuloModel {
  constructor() {
    this.articulos = [
      { id: 1, nombre: "Lavandina x 1L", precio: 875.25, stock: 3000 },
      { id: 4, nombre: "Detergente x 500mL", precio: 1102.45, stock: 2010 },
      { id: 22, nombre: "Jabón en polvo x 250g", precio: 650.22, stock: 407 }
    ];
  }

  listarArticulos() {
    return this.articulos;
  }

  agregarArticulo(id, nombre, precio, stock) {
    this.articulos.push({ id, nombre, precio, stock });
  }

  editarArticulo(id, nuevoNombre, nuevoPrecio, nuevoStock) {
    let art = this.articulos.find(a => a.id === id);
    if (art) {
      art.nombre = nuevoNombre;
      art.precio = nuevoPrecio;
      art.stock = nuevoStock;
      return true;
    }
    return false;
  }

  eliminarArticulo(id) {
    let index = this.articulos.findIndex(a => a.id === id);
    if (index !== -1) {
      this.articulos.splice(index, 1);
      return true;
    }
    return false;
  }

  comprarArticulo(id, cantidad) {
    let art = this.articulos.find(a => a.id === id);
    if (!art || art.stock < cantidad) return null;
    art.stock -= cantidad;
    return art.precio * cantidad;
  }
}

export { ArticuloModel };
