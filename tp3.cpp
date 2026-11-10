// TP 3 — Statistiques d'une série de notes
#include <format>
#include <print>
#include <vector>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>


constexpr std::size_t nbMentions = 5;
constexpr double noteMin = 0.0;
constexpr double noteMax = 20.0;
constexpr double seuilValidation = 10.0;

enum class Mention { Ajourne, Passable, AssezBien, Bien, TresBien };

Mention mentionPour(double note)
{
    if (note < seuilValidation) { return Mention::Ajourne; }
    if (note < 12.0) { return Mention::Passable; }
    if (note < 14.0) { return Mention::AssezBien; }
    if (note < 16.0) { return Mention::Bien; }
    return Mention::TresBien;
}

std::string_view libelle(Mention m)
{
    using enum Mention;
    switch (m) {
    case Ajourne:   return "Ajourné";
    case Passable:  return "Passable";
    case AssezBien: return "Assez bien";
    case Bien:      return "Bien";
    case TresBien:  return "Très bien";
    }
    return "Inconnue";
}
int lireEntier(std::string_view invite, int min, int max)
{
    while (true) {
        std::cout << invite;
        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            return min; // fin d'entrée : valeur de repli
        }
        std::istringstream flux{ligne};
        int valeur{};
        char reste{};
        if (!(flux >> valeur) || (flux >> reste)) {
            std::cout << "  Saisie invalide : entrez un nombre entier.\n";
        } else if (valeur < min || valeur > max) {
            std::cout << "  La valeur doit être comprise entre " << min << " et " << max << ".\n";
        } else {
            return valeur;
        }
    }
}

double lireNote(std::string_view invite)
{
    while (true) {
        std::cout << invite;
        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            return noteMin;
        }
        for (char& c : ligne) {
            if (c == ',') { c = '.'; } // accepter la virgule décimale
        }
        std::istringstream flux{ligne};
        double note{};
        char reste{};
        if (!(flux >> note) || (flux >> reste)) {
            std::cout << "  Saisie invalide.\n";
        } else if (note < noteMin || note > noteMax) {
            std::cout << "  La note doit être comprise entre 0 et 20.\n";
        } else {
            return note;
        }
    }
}
int main()
{
    std::cout << "Nom de l'UE : ";
    std::string ue;
    std::getline(std::cin, ue);

    const int nb = lireEntier("Nombre d'étudiants (1 à 200) : ", 1, 200);

    std::vector<double> notes;
    for (int i{1}; i <= nb; ++i) {
        notes.push_back(lireNote(std::format("Note de l'étudiant {} : ", i)));
    }

    // Affichage provisoire pour vérifier la saisie (on le remplacera)
    std::println("\n{} : {} notes lues", ue, notes.size());
}