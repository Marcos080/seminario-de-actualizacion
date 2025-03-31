#include <iostream>
using namespace std;

struct Cliente {
    string usuario;
    string contraseña;
};

void PedirCredencial(string &usuario, string &contraseña) {
    cout << "Ingrese un usuario: ";
    cin >> usuario;
    cout << "Ingrese una contrasena: ";
    cin >> contraseña;
}

bool VerificacionCredencial(Cliente &usuarioCorrecto) {
    string usuarioIngresado, contraseñaIngresada;
    const int MAXintentos = 3;
    int intentos = 0;

    while (intentos < MAXintentos) {
        PedirCredencial(usuarioIngresado, contraseñaIngresada);

        if (usuarioIngresado == usuarioCorrecto.usuario && 
            contraseñaIngresada == usuarioCorrecto.contraseña) {
            cout << "Bienvenido, " << usuarioCorrecto.usuario << "!" << endl;
            return true;
        } else {
            cout << "Usuario o contrasena incorrectos. Intento " 
                 << intentos + 1 << " de " << MAXintentos << endl;
        }

        intentos++;
    }

    cout << "Usuario bloqueado por exceso de intentos fallidos." << endl;
    return false;
}

void Cambiarcontraseña(Cliente &usuario) {
    string nuevacontraseña;
    cout << "Ingrese su nueva contrasena: ";
    cin >> nuevacontraseña;
    usuario.contraseña = nuevacontraseña;
    cout << "Contraseña actualizada exitosamente!" << endl;
}

void MostrarMenu(Cliente &usuario) {
    int opcion;
    do {
        cout << "\n---- MENU ----\n";
        cout << "1. Modificar contrasena\n";
        cout << "2. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            Cambiarcontraseña(usuario);
            break;
        case 2:
            cout << "Saliendo al inicio del sistema...\n";
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 2);
}

int main() {
    Cliente UsuarioCorrecto = {"jose", "2468"};
    while (true) {
        if (VerificacionCredencial(UsuarioCorrecto)) {
            MostrarMenu(UsuarioCorrecto);
        }
    }
    return 0;
}
