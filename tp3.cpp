// TP 3 — Statistiques d'une série de notes
#include <cstddef>
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

int main() {}