/*Juego de los pancakes resuelto con el método de búsqueda IDAStar.
Se usa una cadena de 9 números y una heuristica que compara los
pancakes con sus vecinos para ver cuántos hay desordenados

Trabajo realizado para la materia de Inteligencia Artificial*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int h4(string state) {
    int h = 0;
    /*recorre la cada pancake excepto el último*/
    for (int i = 0; i < state.size() - 1; i++)
    {
        /*se compara la diferencia absoluta entre los valores para ver
        si estan en orden*/
        if (abs(state[i] - state[i+1]) != 1) {
            /*si no están en orden la heuristica aumenta*/
            h++;
        }
    }
    return h;
/*Se calcula la heuristica por medio de la comparacion de cada
pancake con su vecino, contando cuantas veces hay dos pancakes
juntos que no estan en su posición correcta (un 8 encima de un 3,
por ejemplo)*/
}


bool is_sorted(string state) {
    return is_sorted(state.begin(), state.end());
/*Funcion que devuelve true si la cadena está acomodada en orden ascendente*/
}

vector<string> get_successors(string state) {
    vector<string> successors;
    int n = state.length();
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            string flip = state.substr(i-1, j-i+1);
            reverse(flip.begin(), flip.end());
            string successor = state.substr(0, i-1) + flip + state.substr(j);
            successors.push_back(successor);
        }
    }
    return successors;
/*Funcion para voltear los pancakes*/
}

bool is_visited(string state, vector<string>& visited) {
    return find(visited.begin(), visited.end(), state) != visited.end();
/*Funcion que evita ver nodos que ya han sido visitado*/
}

bool ida_search(string state, int cost, int threshold, int& num_visited, vector<string>& visited, vector<string>& visited_states) {
    num_visited++;
    visited_states.push_back(state);
    int f = cost + h4(state);
    if (f > threshold) {
        return false;
    /*si f es mayor que el umbral la búsqueda no debe continuar por esa rama/nodo*/
    }
    if (is_sorted(state)) {
        return true;
    /*Si el estado actual es la solución se devuelve true*/
    }
    int min_cost = INT_MAX;
    vector<string> successors = get_successors(state); //si no, se generan los sucesores del estado actual
    for (string succ : successors)/*Se itera por cada sucesor para evaluarlo*/ {
        if (!is_visited(succ, visited)/*si el suscesor no ha sido visitado*/) {
            visited.push_back(succ)/*se agrega a la lista de visitados*/;
            bool found = ida_search(succ, cost+1, threshold, num_visited, visited, visited_states);//Y se llama recursivamente a la funcion IDA
            if (found) {
                return true;
            /*Si se encuentra la solucion se devuelve true*/
            }
            visited.pop_back();//si no, se elimina el nodo o sucesor de los visitados y se continua iterando en los otros
        }
    }
    return false;//si en ningun sucesor se encuentra la solucion se devuelve false
}

bool solve_pancakes(string start_state) {
    int threshold = h4(start_state);
    int num_visited = 0;
    vector<string> visited;
    vector<string> visited_states;
    visited.push_back(start_state);
    while (true) {
        bool found = ida_search(start_state, 0, threshold, num_visited, visited, visited_states);
        if (found) {
            cout << "Solucion encontrada en  " << threshold << " movimientos.\n";
            cout << "Se visitaron " << num_visited << " nodos.\n";
            return true;
        }
        if (threshold == INT_MAX) {
            cout << "No se encontro la solucion.\n";
            return false;
        }
        threshold++;
        visited.clear();
        visited.push_back(start_state);
    }
}

int main() {
    string start_state;
    cout << "Ingrese los pancakes desordenados del 1 al 9, sin espacios: ";
    cin >> start_state;
    if (start_state.length() != 9) {
        cout << "Entrada inválida\n";
        return 0;
    }
    if (!solve_pancakes(start_state)) {
        cout << "No se encontro solucion para esta cadena.\n";
    }
    return 0;
}
