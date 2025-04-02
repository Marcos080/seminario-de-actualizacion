#include <iostream>
#include <vector>
using namespace std;

struct Cliente {
    string usuario;
    string contrasena;
};

struct Articulo {
    int id;
    string nombre;
    float precio;
    int stock;
};

void PedirCredencial(string &usuario, string &contrasena) {
    cout << "Ingrese un usuario: ";
    cin >> usuario;
    cout << "Ingrese una contrasena: ";
    cin >> contrasena;
}

bool VerificacionCredencial(Cliente &usuarioCorrecto) {
    string usuarioIngresado, contrasenaIngresada;
    const int MAXintentos = 3;
    int intentos = 0;

    while (intentos < MAXintentos) {
        PedirCredencial(usuarioIngresado, contrasenaIngresada);

        if (usuarioIngresado == usuarioCorrecto.usuario && 
            contrasenaIngresada == usuarioCorrecto.contrasena) {
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

bool ValidarContrasena(const string &contrasena) {
    if (contrasena.length() < 8 || contrasena.length() > 16) {
        return false;
    }
    
    bool tieneMayuscula = false;
    int contadorEspeciales = 0;
    char especiales[] = "!@#$%^&*()-_=+[]{};:'\"<>,.?/|\\";

    for (size_t i = 0; i < contrasena.length(); i++) {
        char c = contrasena[i];
        if (c >= 'A' && c <= 'Z') {
            tieneMayuscula = true;
        }
        for (size_t j = 0; especiales[j] != '\0'; j++) {
            if (c == especiales[j]) {
                contadorEspeciales++;
                break;
            }
        }
    }

    return tieneMayuscula && contadorEspeciales >= 2;
}

void CambiarContrasena(Cliente &usuario) {
    string nuevaContrasena;
    do {
        cout << "Ingrese su nueva contrasena (8-16 caracteres, al menos 1 mayuscula, al menos 2 simbolos especiales): ";
        cin >> nuevaContrasena;
        if (!ValidarContrasena(nuevaContrasena)) {
            cout << "La contrasena no cumple con los requisitos de seguridad. Intente nuevamente.\n";
        }
    } while (!ValidarContrasena(nuevaContrasena));
    
    usuario.contrasena = nuevaContrasena;
    cout << "Contrasena actualizada exitosamente!" << endl;
}

void CrearCuenta(Cliente &usuario) {
    string nuevoUsuario, nuevaContrasena;
    cout << "\n--- Crear Cuenta ---\n";
    cout << "Ingrese un nombre de usuario: ";
    cin >> nuevoUsuario;
    
    do {
        cout << "Ingrese una contrasena (8-16 caracteres, al menos 1 mayuscula, al menos 2 simbolos especiales): ";
        cin >> nuevaContrasena;
        if (!ValidarContrasena(nuevaContrasena)) {
            cout << "La contrasena no cumple con los requisitos de seguridad. Intente nuevamente.\n";
        }
    } while (!ValidarContrasena(nuevaContrasena));
    
    usuario.usuario = nuevoUsuario;
    usuario.contrasena = nuevaContrasena;
    cout << "Cuenta creada exitosamente!" << endl;
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
            CambiarContrasena(usuario);
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

void MostrarArticulos(const vector<Articulo> &articulos) {
    cout << "\n--- Articulos de Limpieza ---\n";
    for (const auto &articulo : articulos) {
        cout << "ID: " << articulo.id << " | Nombre: " << articulo.nombre 
             << " | Precio: " << articulo.precio << " | Stock: " << articulo.stock << endl;
    }
}

int main() {

    vector<Articulo> articulos = {
        {1, "Lavandina x 1L", 875.25, 3000},
        {4, "Detergente x 500mL", 1102.45, 2010},
        {22, "Jabón en polvo x 250g", 650.22, 407}
    };

    Cliente usuario = {"", ""};
    int opcion;

    while (true) {
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. Iniciar sesion\n";
        cout << "2. Crear cuenta\n";
        cout << "3. Ver articulos de limpieza\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            if (usuario.usuario.empty()) {
                cout << "No hay cuentas registradas. Cree una cuenta primero.\n";
            } else if (VerificacionCredencial(usuario)) {
                MostrarMenu(usuario);
            }
            break;
        case 2:
            CrearCuenta(usuario);
            break;
        case 3:
            MostrarArticulos(articulos);
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
            break;
        }
    }
    return 0;
}
