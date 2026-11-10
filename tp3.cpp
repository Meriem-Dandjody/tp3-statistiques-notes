// TP 3 — Statistiques d'une série de notes
#include <format>
#include <print>
#include <vector>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <cmath>

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

        double minimum{noteMax};
    double maximum{noteMin};
    double somme{0.0};
    int admis{0};
    std::array<int, nbMentions> repartition{};

    for (double n : notes) {
        minimum = std::min(minimum, n);
        maximum = std::max(maximum, n);
        somme += n;
        if (n >= seuilValidation) { ++admis; }
        ++repartition[static_cast<std::size_t>(mentionPour(n))];
    }

      const double taille = static_cast<double>(notes.size());
    const double moyenne = somme / taille;

    double sommeEcarts{0.0};
    for (double n : notes) {
        sommeEcarts += (n - moyenne) * (n - moyenne);
    }
    const double ecartType = std::sqrt(sommeEcarts / taille);

    // Affichage provisoire (on le remplacera à l'étape 6)
    std::println("\nmoyenne = {:.2f}, écart-type = {:.2f}", moyenne, ecartType);  
}