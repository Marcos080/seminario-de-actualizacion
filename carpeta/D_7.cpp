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

vector<Articulo> articulos = {
    {1, "Lavandina x 1L", 875.25, 3000},
    {4, "Detergente x 500mL", 1102.45, 2010},
    {22, "Jabón en polvo x 250g", 650.22, 407}
};

void ListarArticulos() {
    if (articulos.empty()) {
        cout << "\nNo hay artículos registrados.\n";
        return;
    }

    cout << "\n--- Listado de Artículos ---\n";
    for (const auto& art : articulos) {
        cout << "ID: " << art.id 
             << " | Nombre: " << art.nombre 
             << " | Precio: $" << art.precio 
             << " | Stock: " << art.stock << endl;
    }
}

void AgregarArticulo() {
    Articulo nuevo;
    cout << "\nIngrese ID: ";
    cin >> nuevo.id;
    cin.ignore();
    cout << "Ingrese Nombre: ";
    getline(cin, nuevo.nombre);
    cout << "Ingrese Precio: ";
    cin >> nuevo.precio;
    cout << "Ingrese Stock: ";
    cin >> nuevo.stock;

    articulos.push_back(nuevo);
    cout << "Artículo agregado correctamente!\n";
}

void EditarArticulo() {
    int id;
    cout << "\nIngrese el ID del artículo a editar: ";
    cin >> id;

    for (auto& art : articulos) {
        if (art.id == id) {
            cin.ignore();
            cout << "Nuevo Nombre (" << art.nombre << "): ";
            getline(cin, art.nombre);
            cout << "Nuevo Precio (" << art.precio << "): ";
            cin >> art.precio;
            cout << "Nuevo Stock (" << art.stock << "): ";
            cin >> art.stock;
            cout << "Artículo actualizado correctamente!\n";
            return;
        }
    }
    cout << "No se encontró un artículo con ese ID.\n";
}

void EliminarArticulo() {
    int id;
    cout << "\nIngrese el ID del artículo a eliminar: ";
    cin >> id;

    for (size_t i = 0; i < articulos.size(); i++) {
        if (articulos[i].id == id) {
            articulos.erase(articulos.begin() + i);
            cout << "Artículo eliminado correctamente!\n";
            return;
        }
    }
    cout << "No se encontró un artículo con ese ID.\n";
}

void ComprarArticulo() {
    int id, cantidad;
    cout << "\nIngrese el ID del artículo que desea comprar: ";
    cin >> id;

    for (auto& art : articulos) {
        if (art.id == id) {
            if (art.stock <= 0) {
                cout << "Lo sentimos, este artículo está agotado.\n";
                return;
            }

            cout << "Ingrese la cantidad a comprar: ";
            cin >> cantidad;

            if (cantidad > art.stock) {
                cout << "No hay suficiente stock disponible. Stock actual: " << art.stock << endl;
                return;
            }

            float total = cantidad * art.precio;
            char confirmacion;
            cout << "El total a pagar es: $" << total << ". ¿Confirmar compra? (S/N): ";
            cin >> confirmacion;

            if (confirmacion == 'S' || confirmacion == 's') {
                art.stock -= cantidad;
                cout << "Compra realizada con éxito! Stock restante: " << art.stock << endl;
            } else {
                cout << "Compra cancelada.\n";
            }
            return;
        }
    }
    cout << "No se encontró un artículo con ese ID.\n";
}

void MenuArticulos() {
    int opcion;
    do {
        cout << "\n--- Gestión de Artículos ---\n";
        cout << "1. Listar artículos\n";
        cout << "2. Agregar artículo\n";
        cout << "3. Editar artículo\n";
        cout << "4. Eliminar artículo\n";
        cout << "5. Comprar artículo\n";
        cout << "6. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: ListarArticulos(); break;
            case 2: AgregarArticulo(); break;
            case 3: EditarArticulo(); break;
            case 4: EliminarArticulo(); break;
            case 5: ComprarArticulo(); break;
            case 6: break;
            default: cout << "Opción inválida. Intente nuevamente.\n"; break;
        }
    } while (opcion != 6);
}

void PedirCredencial(string &usuario, string &contrasena) {
    cout << "Ingrese un usuario: ";
    cin >> usuario;
    cout << "Ingrese una contraseña: ";
    cin >> contrasena;
}

bool VerificacionCredencial(Cliente &usuarioCorrecto) {
    string usuarioIngresado, contrasenaIngresada;
    const int MAXintentos = 3;
    int intentos = 0;

    while (intentos < MAXintentos) {
        PedirCredencial(usuarioIngresado, contrasenaIngresada);
        if (usuarioIngresado == usuarioCorrecto.usuario && contrasenaIngresada == usuarioCorrecto.contrasena) {
            cout << "Bienvenido, " << usuarioCorrecto.usuario << "!\n";
            return true;
        } else {
            cout << "Usuario o contraseña incorrectos. Intento " << intentos + 1 << " de " << MAXintentos << endl;
        }
        intentos++;
    }

    cout << "Usuario bloqueado por exceso de intentos fallidos.\n";
    return false;
}

bool ValidarContrasena(const string &contrasena) {
    if (contrasena.length() < 8 || contrasena.length() > 16) return false;

    bool tieneMayuscula = false;
    int contadorEspeciales = 0;
    char especiales[] = "!@#$%^&*()-_=+[]{};:'\"<>,.?/|\\";

    for (size_t i = 0; i < contrasena.length(); i++) {
        char c = contrasena[i];
        if (c >= 'A' && c <= 'Z') tieneMayuscula = true;
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
        cout << "Ingrese su nueva contraseña (8-16 caracteres, al menos 1 mayúscula, al menos 2 símbolos especiales): ";
        cin >> nuevaContrasena;
        if (!ValidarContrasena(nuevaContrasena)) {
            cout << "La contraseña no cumple con los requisitos de seguridad. Intente nuevamente.\n";
        }
    } while (!ValidarContrasena(nuevaContrasena));

    usuario.contrasena = nuevaContrasena;
    cout << "Contraseña actualizada exitosamente!\n";
}

void CrearCuenta(Cliente &usuario) {
    cout << "\n--- Crear Cuenta ---\n";
    cout << "Ingrese un nombre de usuario: ";
    cin >> usuario.usuario;
    cout << "Ingrese una contraseña: ";
    cin >> usuario.contrasena;
    cout << "Cuenta creada exitosamente!\n";
}

void MostrarMenu(Cliente &usuario) {
    int opcion;
    do {
        cout << "\n---- MENU ----\n";
        cout << "1. Gestionar artículos de limpieza\n";
        cout << "2. Cambiar contraseña\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: MenuArticulos(); break;
            case 2: CambiarContrasena(usuario); break;
            case 3: cout << "Saliendo del sistema...\n"; return;
            default: cout << "Opción inválida. Intente nuevamente.\n"; break;
        }
    } while (opcion != 3);
}

int main() {
    Cliente usuario = {"", ""};
    int opcion;

    while (true) {
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. Iniciar sesión\n";
        cout << "2. Crear cuenta\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
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
                cout << "Saliendo del programa...\n";
                return 0;
            default:
                cout << "Opción inválida. Intente nuevamente.\n";
                break;
        }
    }
}
