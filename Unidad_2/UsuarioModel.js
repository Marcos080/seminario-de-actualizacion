class UsuarioModel {
  constructor() {
    this.TipoUsuario = {
      ADMINISTRADOR: 0,
      CLIENTE: 1,
      VENDEDOR: 2,
      DEPOSITO: 3
    };

    this.usuarios = [
      { usuario: "admin", contrasena: "Admin123!!", tipo: this.TipoUsuario.ADMINISTRADOR },
      { usuario: "cliente", contrasena: "Cliente123!!", tipo: this.TipoUsuario.CLIENTE },
      { usuario: "vendedor", contrasena: "Vendedor123!!", tipo: this.TipoUsuario.VENDEDOR },
      { usuario: "deposito", contrasena: "Deposito123!!", tipo: this.TipoUsuario.DEPOSITO }
    ];
  }

  validarContrasena(contra) {
    if (contra.length < 8 || contra.length > 16) return false;
    let mayus = /[A-Z]/.test(contra);
    let especiales = contra.match(/[!@#$%^&*()\[\]{}\-_=+;:'"<>,.?/|\\]/g);
    return mayus && especiales && especiales.length >= 2;
  }

  cambiarContrasena(usuario, nueva) {
    if (this.validarContrasena(nueva)) {
      usuario.contrasena = nueva;
      return true;
    }
    return false;
  }

  verificarCredenciales(user, pass) {
    return this.usuarios.find(u => u.usuario === user && u.contrasena === pass);
  }

  listarUsuarios() {
    return this.usuarios.map(u => ({ usuario: u.usuario, tipo: u.tipo }));
  }
}

export { UsuarioModel };
