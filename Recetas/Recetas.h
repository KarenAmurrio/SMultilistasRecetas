#pragma once
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Collections::Generic; // Incluimos la librería System::Collections::Generic para poder usar List

namespace Recetas {
    public ref class Nodo {
    public:
        int id;
        property String^ nombre;
        property String^ estado;
        property String^ origen;
        int valorNutricional;
        int cantidad;
        property String^ unidadMedida;
        Nodo^ sig;

    public:
        Nodo() {
            id = 0;
            nombre = "";
            estado = "";
            origen = "";
            valorNutricional = 0;
            cantidad = 0;
            unidadMedida = "";
            sig = nullptr;
        }; // Constructor predeterminado
        Nodo(int _id, String^ _nombre, String^ _estado, String^ _origen, int _valorNutricional, int _cantidad, String^ _unidadMedida) {
            id = _id;
            nombre = _nombre;
            estado = _estado;
            origen = _origen;
            valorNutricional = _valorNutricional;
            cantidad = _cantidad;
            unidadMedida = _unidadMedida;
            sig = nullptr;
        }; // Constructor con parámetros
        ~Nodo() {}; // Destructor
    };

    public ref class receta
    {
    public:
        int identificador;
        String^ nombre;
        String^ tiempoPreparacion;
        String^ tiempoCoccion;
        String^ porciones;
        String^ nivelDificultad;
        String^ categoria;
        String^ origen;
        int valorNutricional;
        Nodo^ cabeza;

    public:
        receta() {
            identificador = 0;
            nombre = "";
            tiempoPreparacion = "";
            tiempoCoccion = "";
            porciones = "";
            nivelDificultad = "";
            categoria = "";
            origen = "";
            valorNutricional = 0;
            cabeza = nullptr;
        }; // Constructor predeterminado
        receta(int _identificador, String^ _nombre, String^ _tiempoPreparacion, String^ _tiempoCoccion, String^ _porciones, String^ _nivelDificultad, String^ _categoria, String^ _origen) {
            identificador = _identificador;
            nombre = _nombre;
            tiempoPreparacion = _tiempoPreparacion;
            tiempoCoccion = _tiempoCoccion;
            porciones = _porciones;
            nivelDificultad = _nivelDificultad;
            categoria = _categoria;
            origen = _origen;
            valorNutricional = 0; // Inicializamos valorNutricional
            cabeza = nullptr; // Inicializamos cabeza
        }; // Constructor con parámetros
        ~receta() {}; // Destructor

        void insertarIngrediente(int _id, String^ _nombre, String^ _estado, String^ _origen, int _valorNutricional, int _cantidad, String^ _unidadMedida) {
            Nodo^ nuevo = gcnew Nodo(_id, _nombre, _estado, _origen, _valorNutricional, _cantidad, _unidadMedida);
            if (cabeza == nullptr) {
                cabeza = nuevo;
            }
            else {
                Nodo^ aux = cabeza;
                while (aux->sig != nullptr) {
                    aux = aux->sig;
                }
                aux->sig = nuevo;
            }
            valorNutricional += nuevo->valorNutricional;
        }; // Método para insertar un ingrediente en la lista de ingredientes de la receta

        void borrarIngrediente(int _id) {
            if (cabeza != nullptr) {
                if (cabeza->id == _id) {
                    Nodo^ aux = cabeza;
                    cabeza = cabeza->sig;
                    valorNutricional -= aux->valorNutricional;
                    delete aux;
                }
                else {
                    Nodo^ aux = cabeza;
                    while (aux->sig != nullptr && aux->sig->id != _id) {
                        aux = aux->sig;
                    }
                    if (aux->sig != nullptr) {
                        Nodo^ aux2 = aux->sig;
                        aux->sig = aux2->sig;
                        valorNutricional -= aux2->valorNutricional;
                        delete aux2;
                    }
                }
            }
        }; // Método para borrar un ingrediente de la lista de ingredientes de la receta

        void mostrarIngredientes(Nodo^ nodo, System::Windows::Forms::ListBox^ listBox) {
            if (nodo != nullptr) {
                listBox->Items->Add("ID: " + nodo->id + "    Nombre: " + nodo->nombre + "    Estado: " + nodo->estado + "    Origen: " + nodo->origen + "    Valor Nutricional: " + nodo->valorNutricional + "    Cantidad: " + nodo->cantidad + "    Unidad de Medida: " + nodo->unidadMedida);
                mostrarIngredientes(nodo->sig, listBox);
                
            }
        }; // Método para mostrar los ingredientes de la receta
    };

    public ref class Multilista {
    public:
        List<receta^>^ multilista; // Vector de punteros a Nodo para almacenar la multilista

    public:
        Multilista() {
            multilista = gcnew List<receta^>(); // Inicializamos la multilista
        }; // Constructor
        ~Multilista() {}; // Destructor

        void eliminarReceta(receta^ Receta) {
            if (Receta != nullptr) {
                multilista->Remove(Receta);
            }
        };

        void insertarReceta(int _identificador, String^ _nombre, String^ _tiempoPreparacion, String^ _tiempoCoccion, String^ _porciones, String^ _nivelDificultad, String^ _categoria, String^ _origen) {
            receta^ nuevo = gcnew receta(_identificador, _nombre, _tiempoPreparacion, _tiempoCoccion, _porciones, _nivelDificultad, _categoria, _origen);
            multilista->Add(nuevo);
        }; // Método para insertar una receta en la multilista

        receta^ buscarReceta(int _identificador) {
            for (int i = 0; i < multilista->Count; i++) { // Recorremos la multilista
                if (multilista[i]->identificador == _identificador) { // Si el identificador de la receta es igual al identificador que buscamos
                    return multilista[i]; // Retornamos la receta
                }
            }
            return nullptr; // Si no se encuentra la receta, retornamos nullptr
        }; // Método para buscar una receta en la multilista
    };
}
