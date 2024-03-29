#include "first_phase.h"
#include "second_phase.h"


char** get_lyndon_words(string* word,vector<int> icfl_list){
    char** list_of_lyndon_words=(char**)malloc(sizeof(char*)*word->length());
    for(int i=0;i<icfl_list.size()-1;i++){
        const char* lyndon_word="\0";
        for (int j=icfl_list[i];j<icfl_list[i+1];j++){
            lyndon_word=append(lyndon_word,word->at(j));
        }
        list_of_lyndon_words[i]=strdup(lyndon_word);
    }
    //L'ultima parola di Lyndon
    const char* lyndon_word="\0";
    for(int i=icfl_list[icfl_list.size()-1];i<word->length();i++){
        lyndon_word=append(lyndon_word,word->at(i));
    }
    list_of_lyndon_words[icfl_list.size()-1]=strdup(lyndon_word);

    return list_of_lyndon_words;
}

suffix_tree_node* creazione_albero(char** list_of_lyndon_words,vector<int> icfl_list,const char* S,int lenght_of_word,int max_size){
    suffix_tree_node* root = build_suffix_tree_node(NULL,"\0",0);
    for(int i=0;i<max_size;i++){
        nodes_vector* last_added_nodes=init_nodes_vector(0);
        suffix_tree_node* temp;
        //Viene elaborato prima l'ultima stringa
        const char* lyndon_word=list_of_lyndon_words[icfl_list.size()-1];
        //if(i<strlen(lyndon_word)){
        if(i< lenght_of_word - icfl_list[icfl_list.size()-1]){
            //La stringa si legge da destra verso sinistra
            //int starting_position= strlen(lyndon_word)-1-i;
            int starting_position= lenght_of_word - icfl_list[icfl_list.size()-1]-1-i;
            temp = add_suffix_in_tree(root,lyndon_word+starting_position,icfl_list[icfl_list.size()-1]+starting_position,i+1);
            if(temp){
                add_in_nodes_vector(last_added_nodes,temp);
            }
        }
        for(int j=0;j<icfl_list.size()-1;j++){
            const char* lyndon_word=list_of_lyndon_words[j];
            if(i<icfl_list[j+1]-icfl_list[j]){
                //La stringa si legge da destra verso sinistra
                int starting_position= icfl_list[j+1]-icfl_list[j]-1-i;
                temp = add_suffix_in_tree(root,lyndon_word+starting_position,icfl_list[j]+starting_position,i+1);
                if(temp){
                    add_in_nodes_vector(last_added_nodes,temp);
                }
            }
        }

        //ELABORA GLI ULTIMI NODI INSERITI
        //cout<<last_added_nodes->used<<endl;
        for(int i=0;i<last_added_nodes->used;i++){
            //cout<<"i: "<<i<<endl;
            create_bit_vector(S,icfl_list,last_added_nodes->data[i]);
            //cout<<last_added_nodes->data[i]->suffix<<endl;
            //print_bit_vector(last_added_nodes->data[i]->bit_vec);
        }

        free(last_added_nodes);
    }
    return root;
}


