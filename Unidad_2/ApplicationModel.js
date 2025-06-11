import { UsuarioModel } from './UsuarioModel.js';
import { ArticuloModel } from './ArticuloModel.js';

class ApplicationModel {
  constructor() {
    this.usuarios = new UsuarioModel();
    this.articulos = new ArticuloModel();
  }
}

export { ApplicationModel };
