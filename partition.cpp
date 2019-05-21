#include "evenement.hpp"
#include "partition.hpp"
#include <algorithm>


struct Clown {
    int ieme;
    int dispo;
};

struct CompHeap {
  CompHeap() {}
  bool operator() (const Clown& a, const Clown& b) {
    return (a.dispo >= b.dispo);
  }
};



// Vous pouvez ajoutez des fonctions et meme des classes dans ce
// fichier, mais vous ne pouvez pas modifier les autres fichiers.

// Cette fonction prend en entree un vecteur d'evenements et retourne une partition de ces evenemnts.
// Chaque vecteur dans la partition correspond aux evenements auquels assiste un clown. L'ordre des
// evenements dans les vecteurs n'a aucune importance.
void partition(const std::vector<Evenement>& evenements,
	       std::vector<std::vector<Evenement> >& partition) {


    std::vector<Evenement> evenements_copie(evenements);
    std::sort(evenements_copie.begin(),evenements_copie.end(), ComparateurDebut());

    std::vector<Clown> clown_heap;
    for (int i = 0; i < evenements_copie.size(); i++){
        clown_heap.push_back(Clown{0, 100,});
    }

    std::vector<Evenement> temp;
    temp.push_back(evenements_copie.front());
    clown_heap.at(0).ieme = 0;
    clown_heap.at(0).dispo = evenements_copie.front().fin();
    partition.push_back(temp);

    std::make_heap(clown_heap.begin(), clown_heap.end(), CompHeap());


    int j = 1;
    for (int i = 1; i < evenements_copie.size(); i++){
            if(clown_heap.at(0).dispo <= evenements_copie.at(i).debut()){
                partition.at(clown_heap.at(0).ieme).push_back(evenements_copie.at(i));
                clown_heap.at(0).dispo = evenements_copie.at(i).fin();
                std::pop_heap(clown_heap.begin(), clown_heap.end(), CompHeap());
                std::push_heap(clown_heap.begin(), clown_heap.end(), CompHeap());
            } else {
                std::vector<Evenement> temp;
                temp.push_back(evenements_copie.at(i));
                clown_heap.at(j).ieme = j;
                clown_heap.at(j).dispo = evenements_copie.at(i).fin();
                partition.push_back(temp);
                std::push_heap(clown_heap.begin(), clown_heap.end(), CompHeap());
                j++;
            }
    }
}
