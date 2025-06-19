import { UsuarioModel, ArticuloModel } from "./ApplicationModel.js"

const StorageManager = {
  guardarUsuarios(usuarioModel) {
    const datos = usuarioModel.usuarios; 
    localStorage.setItem("usuarios", JSON.stringify(datos));
  },

  cargarUsuarios() {
    const data = JSON.parse(localStorage.getItem("usuarios"));
    const usuarioModel = new UsuarioModel();

    if (data) {
      usuarioModel.usuarios = data;
    }

    return usuarioModel;
  },

  guardarArticulos(articuloModel) {
    const datos = articuloModel.articulos;
    localStorage.setItem("articulos", JSON.stringify(datos));
  },

  cargarArticulos() {
    const data = JSON.parse(localStorage.getItem("articulos"));
    const articuloModel = new ArticuloModel();

    if (data) {
      articuloModel.articulos = data;
    }

    return articuloModel;
  }
};

export { StorageManager };