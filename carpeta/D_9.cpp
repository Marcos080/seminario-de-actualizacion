#include <iostream>
#include <vector>

using namespace std;

enum TipoUsuario { ADMINISTRADOR, CLIENTE, VENDEDOR, DEPOSITO };

struct Cliente {
    string usuario;
    string contrasena;
    TipoUsuario tipo;
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

// Usuarios predefinidos
vector<Cliente> usuarios = {
    {"admin", "Admin123!!", ADMINISTRADOR},
    {"cliente", "Cliente123!!", CLIENTE},
    {"vendedor", "Vendedor123!!", VENDEDOR},
    {"deposito", "Deposito123!!", DEPOSITO}
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

Cliente* VerificarCredenciales() {
    string usuario, contrasena;
    int intentos = 0;

    while (intentos < 3) {
        cout << "Ingrese usuario: ";
        cin >> usuario;
        cout << "Ingrese contraseña: ";
        cin >> contrasena;

        for (auto &u : usuarios) {
            if (u.usuario == usuario && u.contrasena == contrasena) {
                cout << "Bienvenido, " << u.usuario << "!\n";
                return &u;
            }
        }

        cout << "Credenciales incorrectas. Intento " << intentos + 1 << " de 3.\n";
        intentos++;
    }

    cout << "Demasiados intentos fallidos.\n";
    return nullptr;
}

// Menús por tipo
void MenuAdministrador(Cliente &usuario) {
    int opcion;
    do {
        cout << "\n--- MENU ADMINISTRADOR ---\n";
        cout << "1. Listar artículos\n";
        cout << "2. Agregar artículo\n";
        cout << "3. Editar artículo\n";
        cout << "4. Eliminar artículo\n";
        cout << "5. Cambiar contraseña\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: ListarArticulos(); break;
            case 2: AgregarArticulo(); break;
            case 3: EditarArticulo(); break;
            case 4: EliminarArticulo(); break;
            case 5: CambiarContrasena(usuario); break;
            case 6: cout << "Cerrando sesión...\n"; break;
            default: cout << "Opción inválida.\n"; break;
        }
    } while (opcion != 6);
}

void MenuCliente(Cliente &usuario) {
    int opcion;
    do {
        cout << "\n--- MENU CLIENTE ---\n";
        cout << "1. Listar artículos\n";
        cout << "2. Comprar artículo\n";
        cout << "3. Cambiar contraseña\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: ListarArticulos(); break;
            case 2: ComprarArticulo(); break;
            case 3: CambiarContrasena(usuario); break;
            case 4: cout << "Cerrando sesión...\n"; break;
            default: cout << "Opción inválida.\n"; break;
        }
    } while (opcion != 4);
}

void MenuVendedor(Cliente &usuario) {
    int opcion;
    do {
        cout << "\n--- MENU VENDEDOR ---\n";
        cout << "1. Listar artículos\n";
        cout << "2. Comprar artículo\n";
        cout << "3. Cambiar contraseña\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: ListarArticulos(); break;
            case 2: ComprarArticulo(); break;
            case 3: CambiarContrasena(usuario); break;
            case 4: cout << "Cerrando sesión...\n"; break;
            default: cout << "Opción inválida.\n"; break;
        }
    } while (opcion != 4);
}

void MenuDeposito(Cliente &usuario) {
    int opcion;
    do {
        cout << "\n--- MENU DEPÓSITO ---\n";
        cout << "1. Listar artículos\n";
        cout << "2. Agregar artículo\n";
        cout << "3. Editar artículo\n";
        cout << "4. Cambiar contraseña\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: ListarArticulos(); break;
            case 2: AgregarArticulo(); break;
            case 3: EditarArticulo(); break;
            case 4: CambiarContrasena(usuario); break;
            case 5: cout << "Cerrando sesión...\n"; break;
            default: cout << "Opción inválida.\n"; break;
        }
    } while (opcion != 5);
}

void MostrarMenuPorTipo(Cliente &usuario) {
    switch (usuario.tipo) {
        case ADMINISTRADOR: MenuAdministrador(usuario); break;
        case CLIENTE: MenuCliente(usuario); break;
        case VENDEDOR: MenuVendedor(usuario); break;
        case DEPOSITO: MenuDeposito(usuario); break;
    }
}

int main() {
    Cliente* usuarioLogueado = VerificarCredenciales();
    if (usuarioLogueado) {
        MostrarMenuPorTipo(*usuarioLogueado);
    }

    return 0;
}
