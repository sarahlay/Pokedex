// Assignment 2 19T3 COMP1511: Pokedex
// pokedex.c
//
// This program was written by Sarah Lay (z5161194)
// on 10/11/2019
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include<string.h>
#include "pokedex.h"

// ----------------------------------------------
// #defines
// ----------------------------------------------
#define FOUND 1
#define NOT_FOUND 0
#define NONE 0
#define HEAD_INDEX 1
#define MATCH 1
#define NOT_MATCH 0
#define DUPLICATE 0
#define UNIQUE 1

// ----------------------------------------------
// type defines
// ----------------------------------------------

typedef struct pokenode *Pokenode;
typedef struct poketype_list *Poketype_list;
typedef struct poketype *Poketype;
typedef struct evolution *Evolution;

// ----------------------------------------------
// structs
// ----------------------------------------------

struct pokedex {
    Pokenode head;
    int size;
    int found_pokemon_count;
    int index;
};

struct pokenode {
    Pokemon pokemon;
    Pokenode next;
    int evolve;
    int status;
};

struct poketype_list {
    Poketype head;
};

struct poketype {
    int type;
    Poketype next;
};


// ----------------------------------------------
// Prototypes for functions
// ----------------------------------------------

// Creates a new Pokedex, and returns a pointer to it.
Pokedex new_pokedex (void);

// Creates a new pokenode struct and returns a pointer to it.
Pokenode new_pokenode (Pokemon pokemon);

// Creates a node for a new type of pokemon
Poketype new_poketype (void);

// Checks that a pokemon with the same id does not already exist, 
// returns FOUND (= 1) if it exists & NOT_FOUND (= 0) if it does not.
int id_duplicate (Pokedex pokedex);

// Creates a list of all the types of Pokemon in the Pokedex, 
// with each type only existing once in the list in the order that
// these types appear in the pokedex.
Poketype_list new_poketype_list (Pokedex pokedex);

// Returns the currently selected Pokenode.
Pokenode get_current_pokenode(Pokedex pokedex);

// A function that returns the pokenode of a pokemon with a given id
Pokenode find_pokemon_id(Pokedex pokedex, int id);

// Sorts the given pokedex into a pokedex in ascending pokemon id order
Pokedex sort_pokedex_id (Pokedex pokedex);

// returns the length of a given string
int string_length (char *string);

// tests if 2 characters match (not case sensitive)
// returns 1 if they match and 0 if they do not
int char_match (char a, char b);

//////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                        //
//////////////////////////////////////////////////////////////////////

// Add a new Pokemon to the Pokedex.
void add_pokemon(Pokedex pokedex, Pokemon pokemon) {
    Pokenode new_node = new_pokenode(pokemon);

    // If the pokedex is empty
    if (pokedex->head == NULL) {
        pokedex->head = new_node;
        pokedex->size = 1;
        pokedex->index = HEAD_INDEX;
        return;
    } 

    // checking that a pokemon with the same id does not already exist
    if (id_duplicate(pokedex)) {
        printf(
            "There's already a Pokemon with pokemon_id %d!\n", 
            pokemon_id(pokemon)
        );
        exit(1);
    }

    // If the pokedex contains 1+ pokenodes
    pokedex->size++;
    Pokenode current_node = pokedex->head;

    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    // Inserting the new pokemon at the end of the pokedex
    current_node->next = new_node;
}

// Return the currently selected Pokemon.
Pokemon get_current_pokemon(Pokedex pokedex) {
    Pokenode current_node = get_current_pokenode(pokedex);
    return current_node->pokemon;
}

// Print out the details of the currently selected Pokemon.
void detail_pokemon(Pokedex pokedex) {
    // do nothing if pokedex is empty
    if (pokedex->head == NULL) {
        return;
    }

    Pokenode current_node = get_current_pokenode(pokedex);
    Pokemon current_pokemon = get_current_pokemon(pokedex);
    
    char *name = pokemon_name(current_pokemon);
    int id = pokemon_id(current_pokemon);
    double height = pokemon_height(current_pokemon);
    double weight = pokemon_weight(current_pokemon);
    int type1 = pokemon_first_type(current_pokemon);
    int type2 = pokemon_second_type(current_pokemon);

    printf("ID: %03d\n", id);
    if (current_node->status == NOT_FOUND) {
        int i = 0;
        printf("Name: ");
        while (name[i] != '\0') {
            printf("*");
            i++;
        }
        printf("\n");
        printf("Height: --\n");
        printf("Weight: --\n");
        printf("Type: --\n");
    } else if (current_node->status == FOUND) {
        printf("Name: %s\n", name);
        printf("Height: %.1lfm\n", height);
        printf("Weight: %.1lfkg\n", weight);
        printf("Type: %s", pokemon_type_to_string(type1));
        if (type2 == NONE) {
            printf("\n");
        } else {
            printf(" %s\n", pokemon_type_to_string(type2));
        }
    } 
}

// Sets the currently selected Pokemon to be 'found'.
void find_current_pokemon(Pokedex pokedex) {
    // return if the pokedex is empty
    if (pokedex->head == NULL) {
        return;
    }

    Pokenode current_node = get_current_pokenode(pokedex);
    if (current_node->status != FOUND) {
        current_node->status = FOUND;
        pokedex->found_pokemon_count++; 
    } 
}

// Print out all of the Pokemon in the Pokedex.
void print_pokemon(Pokedex pokedex) {
    // do nothing if the pokedex is empty
    if (pokedex->head == NULL) {
        return;
    }

    Pokenode current_node = pokedex->head;
    while(current_node != NULL) {
        char *current_name = pokemon_name(current_node->pokemon);
        int current_id = pokemon_id(current_node->pokemon);

        // printing an arrow pointer if the current pokemon is being printed 
        if (current_node == get_current_pokenode(pokedex)) {
            printf("--> #%03d: ", current_id);
        } else {
            printf("    #%03d: ", current_id);
        }

        if (current_node->status == FOUND) {
            printf("%s\n", current_name);
        } else {
            int i = 0;
            while(current_name[i] != '\0') {
                printf("*");
                i++;
            }
            printf("\n");
        }
        current_node = current_node->next;
    } 
}

//////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                        //
//////////////////////////////////////////////////////////////////////

// Change the currently selected Pokemon to be the next Pokemon in the Pokedex.
void next_pokemon(Pokedex pokedex) {
    // return if the pokedex is empty
    if (pokedex->head == NULL) {
        return;
    }

    if (pokedex->index < pokedex->size) {
        pokedex->index++;
    }
}

// Change the currently selected Pokemon to be the previous 
// Pokemon in the Pokedex.
void prev_pokemon(Pokedex pokedex) {
    // do nothing if the pokedex is empty
    if (pokedex->head == NULL) {
        return;
    }   

    if (pokedex->index > HEAD_INDEX) {
        pokedex->index--;
    }
}

// Change the currently selected Pokemon to be the Pokemon with the ID `id`.
void change_current_pokemon(Pokedex pokedex, int id) {
    // do nothing if the pokedex is empty
    if (pokedex->head == NULL) {
        return;
    }

    int original_index = pokedex->index;
    pokedex->index = HEAD_INDEX;
    Pokenode current_node = get_current_pokenode(pokedex);
    int current_id = pokemon_id(current_node->pokemon);    

    // looping through the pokedex until the id matches
    while (current_id != id) {
        // if the id does not exist in the pokedex,
        // return original index
        if (pokedex->index == pokedex->size) {
            pokedex->index = original_index;
            return;
        }
        pokedex->index++;
        current_node = get_current_pokenode(pokedex);
        current_id = pokemon_id(current_node->pokemon);        
    }

}

// Remove the currently selected Pokemon from the Pokedex.
void remove_pokemon(Pokedex pokedex) {
    // if pokedex is empty, do nothing
    if (pokedex->head == NULL) {
    return;
    }

    // storing the removal node and index
    Pokenode removal_node = get_current_pokenode(pokedex);
    int removal_index = pokedex->index;
    pokedex->size--;

    // reduce the found_pokemon_count by 1 if it was found
    if (removal_node->status == FOUND) {
        pokedex->found_pokemon_count--;
    }

    // if removing head
    if (removal_node == pokedex->head) {
        pokedex->head = pokedex->head->next;
        destroy_pokemon(removal_node->pokemon);
        free(removal_node);
        return;
    }

    // storing the previous node 
    prev_pokemon(pokedex);
    Pokenode previous_node = get_current_pokenode(pokedex);

    // if removing last node
    if (removal_node->next == NULL) {
        previous_node->next = NULL;
        destroy_pokemon(removal_node->pokemon);
        free(removal_node);
        return;
    }

    // if removing any node between the head and the last node
    previous_node->next = removal_node->next;

    // redirecting the current pokemon (index)
    if (removal_node->next != NULL) {
        pokedex->index = removal_index;
    } 

    destroy_pokemon(removal_node->pokemon);
    free(removal_node);
}

// Destroy the given Pokedex and free all associated memory.
void destroy_pokedex(Pokedex pokedex) {
    // if the pokedex is empty
    if (pokedex->head == NULL) {
        free(pokedex);        
        return;
    }

    Pokenode current_node = pokedex->head;

    // looping through all the nodes and freeing their memory
    current_node = pokedex->head;
    while (current_node->next != NULL) {
        Pokenode temp_node = current_node;
        current_node = current_node->next;
        destroy_pokemon(temp_node->pokemon);
        free(temp_node);
    }

    // free memory of the last node
    destroy_pokemon(current_node->pokemon);
    free(current_node);

    // free memory of the pokedex
    free(pokedex);
}

//////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                        //
//////////////////////////////////////////////////////////////////////
// Frees the poketypes list
void free_poketypes (Poketype_list poketype_list) {
    Poketype current_type = poketype_list->head;
    while (current_type != NULL) {
        Poketype temp = current_type;
        current_type = current_type->next;
        free(temp);
    }
    free(poketype_list);
}

// Print out all of the different types of Pokemon in the Pokedex.
void show_types(Pokedex pokedex) {
    // do nothing if the pokedex is empty
    if (pokedex->head == NULL) {
        return;
    }

    Poketype_list poketypes = new_poketype_list(pokedex);
    Poketype current_type = poketypes->head;

    while (current_type != NULL) {
        printf("%s\n", pokemon_type_to_string(current_type->type));
        current_type = current_type->next;
    }

    free_poketypes(poketypes);
}

// Set the first not-yet-found Pokemon of each type to be found.
void go_exploring(Pokedex pokedex) {
    // do nothing if the pokedex is empty
    if (pokedex->head == NULL) {
        return;
    }

    // Initialising the current pointers.
    int original_index = pokedex->index;
    Poketype_list poketypes = new_poketype_list(pokedex);
    Poketype current_poketype = poketypes->head;

    // looping through the pokedex, if the current pokemon's type matches
    // an element in the poketype_list and is not found,
    // the program will set the current pokemon to be found.
    while (current_poketype != NULL) {
        pokedex->index = HEAD_INDEX;
        while (pokedex->index <= pokedex->size) {
            Pokenode current_node = get_current_pokenode(pokedex);
            if (current_node->status == NOT_FOUND &&
                pokemon_first_type (current_node->pokemon) == 
                current_poketype->type 
            ) {               
                find_current_pokemon(pokedex);
                break;
            }         
            pokedex->index++;        
        }
        current_poketype = current_poketype->next;
    }
    pokedex->index = original_index;
    free_poketypes(poketypes);
}

// Return the total number of Pokemon in the Pokedex.
int count_total_pokemon(Pokedex pokedex) {
    return pokedex->size;
}

// Return the number of Pokemon in the Pokedex that have been found.
int count_found_pokemon(Pokedex pokedex) {
    return pokedex->found_pokemon_count;
}


//////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                        //
//////////////////////////////////////////////////////////////////////
 
// Add the information that the Pokemon with the ID `from_id` can
// evolve into the Pokemon with the ID `to_id`.
void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id) {
    if (pokedex->head == NULL || pokedex->head->next == NULL) {
        printf("Invalid Pokemon Evolution!\n");
        exit(1);
    }

    // checking if the pokemon with the from_id and to_id exists in the pokedex
    int from_id_exist = NOT_FOUND;
    int to_id_exist = NOT_FOUND;
    Pokenode current_node = pokedex->head;
    while (current_node != NULL) {
        if (pokemon_id(current_node->pokemon) == from_id) {
            from_id_exist += FOUND;
        }

        if (pokemon_id(current_node->pokemon) == to_id) {
            to_id_exist += FOUND;
        }
        current_node = current_node->next;
    }

    if (from_id_exist == NOT_FOUND || to_id_exist == NOT_FOUND) {
        printf("Invalid Pokemon Evolution!\n");
        exit(1);
    }

    // If there are no errors, assign id's to the pokemon's evolution
    int original_index = pokedex->index;
    change_current_pokemon(pokedex, from_id);
    current_node = get_current_pokenode(pokedex);

    current_node->evolve = to_id;
    pokedex->index = original_index;
}

// Show the evolutions of the currently selected Pokemon.
void show_evolutions(Pokedex pokedex) {
    // do nothing if the pokedex is empty
    if (pokedex->head == NULL) {
        return;
    }
    // looping through and printing out the evolutions
    Pokenode evolve_pokenode = get_current_pokenode(pokedex);
    int id = pokemon_id(evolve_pokenode->pokemon);

    while (id != NONE) {

        char *name = pokemon_name(evolve_pokenode->pokemon);
        pokemon_type type1 = pokemon_first_type(evolve_pokenode->pokemon);
        pokemon_type type2 = pokemon_second_type(evolve_pokenode->pokemon);

        // this will print out the current pokemon
        if (evolve_pokenode->status == FOUND) {
            printf("#%03d %s [%s", id, name, pokemon_type_to_string(type1));
            if (type2 != NONE_TYPE) {
                printf(" %s]", pokemon_type_to_string(type2));
            } else {
                printf("]");
            }
        } else {
            printf("#%03d ???? [????] ", id);
        }

        // changing the id to the next evolution
        id = evolve_pokenode->evolve;

        // finding the next evolution
        evolve_pokenode = find_pokemon_id(pokedex, id);

        // checking that the next evolution exists and returning if it does not.
        if (id != NONE && evolve_pokenode != NULL) {
            printf("--> "); 
        } else {
            printf("\n");
            return;
        }
    }
}

// Return the pokemon_id of the Pokemon that the currently selected
// Pokemon evolves into.
int get_next_evolution(Pokedex pokedex) {
    if (pokedex->head == NULL) {
        printf("The Pokedex is empty!\n");
        exit(1);
    }

    Pokenode current_node = get_current_pokenode(pokedex);
    if (current_node->evolve == NONE) {
        return DOES_NOT_EVOLVE;
    } else {
        if (find_pokemon_id(pokedex, current_node->evolve) == NULL) {
            return DOES_NOT_EVOLVE;
        } else {
            return current_node->evolve;
        }
    }

}

//////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                        //
//////////////////////////////////////////////////////////////////////

// Create a new Pokedex which contains only the Pokemon of a specified
// type from the original Pokedex.
Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {
    Pokedex typedex = new_pokedex();
    if (pokedex->head == NULL) {
        return typedex;
    }

    if (type == NONE_TYPE || type == INVALID_TYPE || type == MAX_TYPE) {
        printf("Invalid type");
        exit(1);
    }

    Pokenode current_node = pokedex->head;

    while (current_node != NULL) {
        pokemon_type type1 = pokemon_first_type(current_node->pokemon);
        pokemon_type type2 = pokemon_second_type(current_node->pokemon);
        
        // if the type matches, then create a clone of the pokemon and 
        // add it to the type_pokedex
        if  (current_node->status == FOUND && 
            (type1 == type || type2 == type)
        ) {
            Pokemon pokemon = clone_pokemon(current_node->pokemon);
            add_pokemon(typedex, pokemon);
            next_pokemon(typedex);
            find_current_pokemon(typedex);
        }
        current_node = current_node->next;
    }
    typedex->index = HEAD_INDEX;
    return typedex;
}

// Create a new Pokedex which contains only the Pokemon that have
// previously been 'found' from the original Pokedex.
Pokedex get_found_pokemon(Pokedex pokedex) {
    Pokedex foundex = new_pokedex();

    // if the pokedex is empty
    if (pokedex->head == NULL) {
        return foundex;
    }
    Pokenode current_node = pokedex->head;

    // adding all the found pokemon into the foundex
    while (current_node != NULL) {
        if (current_node->status == FOUND) {
            Pokemon pokemon = clone_pokemon(current_node->pokemon);
            add_pokemon(foundex, pokemon);
            next_pokemon(foundex);
            find_current_pokemon(foundex);
        }
        current_node = current_node->next;
    }

    // sorting the foundex by id 
    if (foundex->head != NULL) {
        foundex = sort_pokedex_id (foundex);
        foundex->index = HEAD_INDEX;
    }
    return foundex;
}

// Create a new Pokedex containing only the Pokemon from the original
// Pokedex which have the given string appearing in its name.
Pokedex search_pokemon(Pokedex pokedex, char *text) {
    Pokedex stringdex = new_pokedex();
    Pokenode current_node = pokedex->head;

    while (current_node != NULL) {
        Pokemon pokemon = current_node->pokemon;
        char *name = pokemon_name(pokemon);
        int i = 0;
        int j = 0;
        int match = NONE;
        while (name[j] != '\0') {

            if (current_node->status == FOUND && char_match(name[j], text[i])) {
                // if both characters match
                match++;
                i++;
            } else if (match == 1 && name[j - 1] == name[j] && i == 1) {
                // if 2 letters are consecutively the same and
                // those letters match the first letter of the given text
                // then retain the index of the text and check again
                i = 1;
            } else {
                match = NONE;
                i = 0;
            }

            if (match > NONE && text[i] == '\0') {
                match = string_length(text);
                break;
            }

            j++;
        }

        if (match == string_length(text)) {
            // if the text matches the pokemon name, 
            // copy the pokemon into the stringdex
            add_pokemon(stringdex, clone_pokemon(pokemon));
            next_pokemon(stringdex);
            find_current_pokemon(stringdex);
        }
        current_node = current_node->next;
    }

    stringdex->index = HEAD_INDEX;
    return stringdex;
}

//////////////////////////////////////////////////////////////////////
//                          Helper Functions                        //
//////////////////////////////////////////////////////////////////////

// Creates a new Pokedex, and returns a pointer to it.
Pokedex new_pokedex (void) {
    // Malloc memory for a new Pokedex, and check that the memory
    // allocation succeeded.
    Pokedex pokedex = malloc(sizeof(struct pokedex));
    assert(pokedex != NULL);

    // Set the head of the linked list to be NULL.
    // (i.e. set the Pokedex to be empty)
    pokedex->head = NULL;
    pokedex->size = NONE;
    pokedex->found_pokemon_count = NONE;    
    pokedex->index = NONE;

    return pokedex;
}

// Create a new pokenode struct and returns a pointer to it.
//
// This function should allocate memory for a pokenode, set its pokemon
// pointer to point to the specified pokemon, and return a pointer to
// the allocated memory.
Pokenode new_pokenode (Pokemon pokemon) {
    Pokenode new_node = malloc(sizeof(struct pokenode));
    new_node->pokemon = pokemon;
    new_node->next = NULL;
    new_node->status = NOT_FOUND;
    new_node->evolve = NONE;
    return new_node;
}

// Creates a node for a new type of pokemon
Poketype new_poketype (void) {
    Poketype new_poketype = malloc(sizeof(struct poketype));
    new_poketype->type = NONE;
    new_poketype->next = NULL;
    return new_poketype;
}

// Checks that a pokemon with the same id does not already exist, 
// returns UNIQUE (= 1) if it is not a duplicate & 
// DUPLICATE (= 0) if it is a duplicate.
int id_duplicate (Pokedex pokedex) {
    // return 0 if pokedex is empty
    if (pokedex->head == NULL) {
        return NONE;
    }

    Pokenode current_node = pokedex->head;
    Pokemon pokemon = current_node->pokemon;
    int id_duplicate = NOT_FOUND;

    while (current_node != NULL) {
        if (pokemon_id(pokemon) == pokemon_id(current_node->pokemon)) {
            id_duplicate = FOUND;
        }
        current_node = current_node->next;
    }

    if (id_duplicate == FOUND) {
        return DUPLICATE;
    } else {
        return UNIQUE;
    }
}


// Creates a list of all the types of Pokemon in the Pokedex, 
// with each type only existing once in the list in the order that
// these types appear in the pokedex.
Poketype_list new_poketype_list (Pokedex pokedex) {

    // create structs for poketype list and initiate the list
    Poketype_list poketypes = malloc(sizeof(struct poketype_list));
    Poketype current_poketype = new_poketype();
    poketypes->head = current_poketype;

    // return if the pokedex is empty
    if (pokedex->head == NULL) {
        return poketypes;
    }

    // if the pokedex is not empty
    // loop through the list and assig the next poketype as
    // the next pokemon type if it does not already exist in the list
    Pokenode current_node = pokedex->head;
    current_poketype->type = pokemon_first_type(current_node->pokemon);
    poketypes->head = current_poketype;
    Poketype assign_type = poketypes->head;

    while (current_node != NULL) {
        int new_type1 = pokemon_first_type(current_node->pokemon);
        int new_type2 = pokemon_second_type(current_node->pokemon);
        int duplicate1 = NOT_FOUND;
        int duplicate2 = NOT_FOUND;

        current_poketype = poketypes->head;

        // for the first poketype
        while (new_type1 != NONE_TYPE && current_poketype != NULL) {
            if (current_poketype->type == new_type1) {
                duplicate1 = FOUND;
            }
            current_poketype = current_poketype->next;
        }
        if (new_type1 != NONE_TYPE && duplicate1 == NOT_FOUND) {
            Poketype add_type = new_poketype();
            add_type->type = new_type1;
            assign_type->next = add_type;
            assign_type = assign_type->next;
        }        

        // for the second poketype
        current_poketype = poketypes->head;
        while (new_type2 != NONE_TYPE && current_poketype != NULL) {
            if (current_poketype->type == new_type2) {
                duplicate2 = FOUND;
            }
            current_poketype = current_poketype->next;
        }        

        if (new_type2 != NONE_TYPE && duplicate2 == NOT_FOUND) {
            Poketype add_type = new_poketype();
            add_type->type = new_type2;
            assign_type->next = add_type;
            assign_type = assign_type->next;
        }

        current_node = current_node->next;
    }
    return poketypes;
}


// Returns the currently selected Pokenode.
Pokenode get_current_pokenode(Pokedex pokedex) {
    Pokenode current_node = pokedex->head;
    int i = HEAD_INDEX;
    while (i < pokedex->index) {
        current_node = current_node->next;
        i++;
    }

    return current_node;
}

// A function that returns the pokenode of a pokemon with a given id
Pokenode find_pokemon_id(Pokedex pokedex, int id) {
    if (pokedex == NULL) {
        return NULL;
    }

    Pokenode current_node = pokedex->head;
    int current_id = 0;
    while (current_node != NULL && current_id != id) {
        current_node = current_node->next;
        if (current_node != NULL) {
            current_id = pokemon_id(current_node->pokemon);
        }
    }

    if (current_id == id) {
        return current_node;
    } else {
        return NULL;
    }
}

// Sorts the given pokedex into a pokedex in ascending pokemon id order
// Returns a pokedex ordered by ascending pokemon id's
Pokedex sort_pokedex_id (Pokedex pokedex) {
    if (pokedex->head == NULL) {
        return NULL;
    }

    Pokenode current_node = pokedex->head;
    Pokenode previous_node = NULL;
    Pokenode next_node = current_node->next;
    

    while (next_node != NULL) {
        int curr_id = pokemon_id(current_node->pokemon);
        int next_id = pokemon_id(next_node->pokemon);

        if (curr_id > next_id) {
            // if the current id is larger than the next, swap the 2 nodes
            if (current_node == pokedex->head) {
                pokedex->head = next_node;
                current_node->next = next_node->next;
                next_node->next = current_node;
            } else {
                current_node->next = next_node->next; 
                next_node->next = current_node;
                previous_node->next = next_node;
            }
            previous_node = NULL;
            current_node = pokedex->head;
            next_node = current_node->next;
        } else {
            previous_node = current_node;
            current_node = current_node->next;
            next_node = current_node->next;
        }
    }

    return pokedex;

}

// returns the length of a given string
int string_length (char *string) {
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }
    return i;
}

// returns 1 if the given characters match and returns 0 if they do not
// (not case sensitive)
int char_match (char a, char b) {
    // uppercase = lowercase
    int diff = 'a' - 'A';

    // checking when uppercase & lowercase is given, 
    // or letters are the same case
    if (a == b - diff || a - diff == b || a == b) {
        return MATCH;
    } else {
        return NOT_MATCH;
    }

}
