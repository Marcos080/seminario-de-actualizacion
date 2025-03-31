#include <iostream>
using namespace std;

struct Cliente {
    string usuario;
    string contraseña;
};


void PedirCredencial(string &usuario, string &contraseña) {
    cout << "Ingrese un usuario: ";
    cin >> usuario;
    cout << "Ingrese una contraseña: ";
    cin >> contraseña;
}


bool VerificacionCredencial(Cliente usuarioCorrecto) {
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
            cout << "Usuario o contraseña incorrectos. Intento " 
                 << intentos + 1 << " de " << MAXintentos << endl;
        }

        intentos++;
    }

    cout << "Usuario bloqueado por exceso de intentos fallidos." << endl;
    return false;
}


int main() {
    Cliente UsuarioCorrecto = {"jose", "2468"};

    VerificacionCredencial(UsuarioCorrecto);

    return 0;
}
