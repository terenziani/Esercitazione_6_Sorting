/* Andrea Terenziani s284817
 *
 * Questo programma serve per confrontare l'efficienza dei metodi di bubblesort e di mergesort
 * a seconda delle caratteristiche del vettore da ordinare.
 * Poichè il tempo impiegato per ordinare un vettore di una data dimensione, può variare su ripetizioni successive
 * anche con l'utilizzo della stessa funzione, useremo la media dei tempi di calcolo per trarre le conclusioni.
 *
 * Le dimensioni dei vettori inoltre, verranno inserite da linea di comando
 *
 * NB! arg_c indica il numero di input passati da linea di comando, e vale sempre almeno 1, ovvero l'eseguibile.
 *     arg_v è invece un vettore di vettori che salva tutti gli input inseriti nella linea di comando.
 *     Se nella linea di comando voglio scrivere più elementi, li dovrò separare con lo spazio.

*/


// Notiamo che per dimensioni di vettori ridotte, la funzione Bubblesort è più rapida
// Più la dimensione aumenta invece, più risulta conveniente utilizzare Mergesort, avendo infatti un costo computazionale di n*log2(n)


#include <iostream>
#include "SortingAlgorithm.hpp"
#include <chrono>
#include <vector>
#include <numeric>

using namespace std;

int main(int argc, char * argv[])
{
    //numero di iterazioni da fare per ogni dimensione di vettore studiata
    int iterazioni = 50;


    //controllo che in input venga fornito almeno un valore nella linea di comando
    if (argc==1)
    {
        cerr<<"Non sono stati forniti valori nella linea di comando";
    }



    //per ogni dimensione di vettori fornita nella linea di comando, faccio le iterazioni desiderate, ciascuna con un vettore random (ma di dimensione fissata)
    for (int i = 1; i <= argc-1; ++i)
    {
        //converto in intero i numeri della linea di comando
        int dimensione=stoi(argv[i]);

        cout<< "La dimensione del vettore e "<<dimensione<<'\n';



        double tempo_merge_tot=0;
        double tempo_bubble_tot=0;

        //calcolo i tempi per ogni iterazione
        for (int k=0; k<=iterazioni-1; ++k)
        {
            //creo il vettore per ciascuna iterazione, inserendo valori interi random compresi tra 0 e 1000 in ogni elemento del vettore
            vector<int> vettore(dimensione);

            for (int j=0 ; j<=dimensione-1 ; ++j)
                vettore[j] = rand() % 1001;




            //faccio una copia dei vettori per non modificare gli originali
            vector<int> vect_merge = vettore;
            vector<int> vect_bubble = vettore;


            //applico MergeSort e calcolo il tempo impiegato
            chrono::steady_clock::time_point t_begin_Merge = chrono::steady_clock::now();
            SortLibrary::MergeSort(vect_merge);
            chrono::steady_clock::time_point t_end_Merge = chrono::steady_clock::now();

            double durata_merge = chrono::duration_cast<chrono::microseconds>(t_end_Merge-t_begin_Merge).count();



            //applico BubbleSort e calcolo il tempo impiegato
            chrono::steady_clock::time_point t_begin_Bubble = chrono::steady_clock::now();
            SortLibrary::BubbleSort(vect_bubble);
            chrono::steady_clock::time_point t_end_Bubble = chrono::steady_clock::now();

            double durata_bubble= chrono::duration_cast<chrono::microseconds>(t_end_Bubble-t_begin_Bubble).count();


            tempo_merge_tot=tempo_merge_tot+durata_merge;
            tempo_bubble_tot=tempo_bubble_tot+durata_bubble;



        }

        //calcolo i tempi medi per ogni dimensione dei vettori studiata
        double t_mean_bubble=tempo_bubble_tot/iterazioni;
        double t_mean_merge=tempo_merge_tot/iterazioni;

        //stampo a video i risultati ottenuti
        cout<<"La durata media di Mergesort e "<<t_mean_merge<<'\n';
        cout<<"La durata media di Bubblesort e "<<t_mean_bubble<<'\n'<<'\n';


    }


    return 0;
}







