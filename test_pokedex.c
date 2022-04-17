// Assignment 2 19T3 COMP1511: Pokedex
// test_pokedex.c
//
// This file allows you to automatically test the functions you
// implement in pokedex.c.
//
// This program was written by Sarah Lay (z5161194)
// on 15-11-2019
//
// Version 1.0.0: Assignment released.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "pokedex.h"

// ----------------------------------------------
// #defines
// ----------------------------------------------

// ----------------------------------------------
// Sample data on pokemon
// ----------------------------------------------

// Bulbasaur
#define BULBASAUR_ID 1
#define BULBASAUR_NAME "Bulbasaur"
#define BULBASAUR_HEIGHT 0.7
#define BULBASAUR_WEIGHT 6.9
#define BULBASAUR_FIRST_TYPE GRASS_TYPE
#define BULBASAUR_SECOND_TYPE POISON_TYPE

// Ivysaur
#define IVYSAUR_ID 2
#define IVYSAUR_NAME "Ivysaur"
#define IVYSAUR_HEIGHT 1.0
#define IVYSAUR_WEIGHT 13.0
#define IVYSAUR_FIRST_TYPE GRASS_TYPE
#define IVYSAUR_SECOND_TYPE POISON_TYPE

// Venusaur
#define VENUSAUR_ID 3
#define VENUSAUR_NAME "Venusaur"
#define VENUSAUR_HEIGHT 2.0
#define VENUSAUR_WEIGHT 100.0
#define VENUSAUR_FIRST_TYPE GRASS_TYPE
#define VENUSAUR_SECOND_TYPE POISON_TYPE

// Psyduck
#define PSYDUCK_ID 54
#define PSYDUCK_NAME "Psyduck"
#define PSYDUCK_HEIGHT 0.8
#define PSYDUCK_WEIGHT 19.6
#define PSYDUCK_FIRST_TYPE WATER_TYPE
#define PSYDUCK_SECOND_TYPE NONE_TYPE

// Golduck
#define GOLDUCK_ID 55
#define GOLDUCK_NAME "Golduck"
#define GOLDUCK_HEIGHT 1.7
#define GOLDUCK_WEIGHT 76.6
#define GOLDUCK_FIRST_TYPE WATER_TYPE
#define GOLDUCK_SECOND_TYPE NONE_TYPE

// Exeggcute
#define EXEGGCUTE_ID 102
#define EXEGGCUTE_NAME "EXEGGCUTE"
#define EXEGGCUTE_HEIGHT 0.4
#define EXEGGCUTE_WEIGHT 2.5
#define EXEGGCUTE_FIRST_TYPE PSYCHIC_TYPE
#define EXEGGCUTE_SECOND_TYPE GRASS_TYPE

// Exeggutor
#define EXEGGUTOR_ID 103
#define EXEGGUTOR_NAME "EXEGGUTOR"
#define EXEGGUTOR_HEIGHT 2.0
#define EXEGGUTOR_WEIGHT 120.0
#define EXEGGUTOR_FIRST_TYPE PSYCHIC_TYPE
#define EXEGGUTOR_SECOND_TYPE GRASS_TYPE

// Mr Mime
#define MRMIME_ID 122
#define MRMIME_NAME "MrMime"
#define MRMIME_HEIGHT 1.3
#define MRMIME_WEIGHT 54.4
#define MRMIME_FIRST_TYPE FAIRY_TYPE
#define MRMIME_SECOND_TYPE PSYCHIC_TYPE

// Ditto
#define DITTO_ID 132
#define DITTO_NAME "Ditto"
#define DITTO_HEIGHT 0.3
#define DITTO_WEIGHT 4.0
#define DITTO_FIRST_TYPE NORMAL_TYPE
#define DITTO_SECOND_TYPE NONE_TYPE


// ----------------------------------------------
// Function Prototypes
// ----------------------------------------------
// create pokemon
static Pokemon create_bulbasaur(void);
static Pokemon create_ivysaur(void);
static Pokemon create_venusaur(void);
static Pokemon create_psyduck(void);
static Pokemon create_golduck(void);
static Pokemon create_exeggcute(void);
static Pokemon create_exeggutor(void);
static Pokemon create_mr_mime(void);
static Pokemon create_ditto(void);

// Tests for Pokedex functions from pokedex.c.
// Tests for Stage One.
static void test_detail_pokemon(void);
static void test_new_pokedex(void);
static void test_add_pokemon(void);
static void test_print_pokemon(void);

// Tests for Stage Two.
static void test_prev_and_next_pokemon(void);
static void test_change_and_remove_pokemon(void);

// Tests for Stage Three.
static void test_show_types(void);
static void test_go_exploring(void);

// Tests for Stage Four.
static void test_evolutions(void);

// Tests for Stage Five.
static void test_get_pokemon_of_type(void);
static void test_get_found_pokemon(void);
static void test_search_pokemon(void);

// Helper functions for creating/comparing Pokemon.
static int is_same_pokemon(Pokemon first, Pokemon second);
static int is_copied_pokemon(Pokemon first, Pokemon second);
Pokedex build_pokedex_6 (Pokedex pokedex);



int main(int argc, char *argv[]) {
    printf("Welcome to the COMP1511 Pokedex Tests!\n");

    printf("\n==================== Pokedex Tests ====================\n");

    // Stage 1 Testing
    test_new_pokedex();
    test_add_pokemon();
    test_detail_pokemon();
    test_print_pokemon();

    // Stage 2 Testing  
    test_prev_and_next_pokemon();
    test_change_and_remove_pokemon();

    // Stage 3 Testing
    test_show_types();
    test_go_exploring();

    // Stage 4 Testing
    test_evolutions();

    // Stage 5 Testing
    test_get_pokemon_of_type();
    test_get_found_pokemon();
    test_search_pokemon();
    

    printf("\nAll Pokedex tests passed, you are AWESOME!\n");
}


////////////////////////////////////////////////////////////////////////
//                     Pokedex Test Functions                         //
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//                      Stage One Testing                             //
////////////////////////////////////////////////////////////////////////

// `test_new_pokedex` checks whether the new_pokedex and destroy_pokedex
// functions work correctly, to the extent that it can.
//
// It does this by creating a new Pokedex, checking that it's not NULL,
// then calling destroy_pokedex.
static void test_new_pokedex(void) {
    printf("\n>> Testing new_pokedex\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("       --> Checking that the returned Pokedex is not NULL\n");
    assert(pokedex != NULL);

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed new_pokedex tests!\n");
}

// `test_add_pokemon` checks whether the add_pokemon function works
// correctly.
//
// It does this by creating the Pokemon Bulbasaur, and
// calling add_pokemon to add it to the Pokedex.
static void test_add_pokemon(void) {
    printf("\n>> Testing add_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Creating Bulbasaur, Ivysaur, Mr Mime and Ditto\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();
    Pokemon mrmime = create_mr_mime();
    Pokemon ditto = create_ditto();

    printf("    ... Adding Bulbasaur, Ivysaur, Mr Mime and Ditto to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    add_pokemon(pokedex, mrmime);
    add_pokemon(pokedex, ditto);

    printf("       --> Checking if add_pokemon functions correctly\n");
    assert(count_total_pokemon(pokedex) == 4);
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));
    next_pokemon(pokedex);
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));
    next_pokemon(pokedex);
    assert(is_same_pokemon(get_current_pokemon(pokedex), mrmime));
    next_pokemon(pokedex);
    assert(is_same_pokemon(get_current_pokemon(pokedex), ditto));
 
    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed add_pokemon tests!\n");
}

// `test_detail_pokemon` checks whether the detail_pokemon function works
// correctly.
//
// It does this by creating the Pokemon Bulbasaur and Ivysaur, and
// calling detail_pokemon to print out the details of the currently
// selected pokemon.
static void test_detail_pokemon(void) {
    printf("\n>> Testing detail_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Testing detail_pokemon on an empty Pokedex\n");   
    detail_pokemon(pokedex);

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(get_current_pokemon(pokedex) == bulbasaur);

    printf("    ... Calling detail_pokemon\n");
    detail_pokemon(pokedex);
    
    printf("    ... Setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);

    printf("    ... Obtaining the details of the current found Pokemon\n");
    detail_pokemon(pokedex);

    printf("    ... Calling next_pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Ivysaur\n");
    assert(get_current_pokemon(pokedex) == ivysaur);

    printf("    ... Calling detail_pokemon\n");
    detail_pokemon(pokedex);
    
    printf("    ... Setting Ivysaur to be found\n");
    find_current_pokemon(pokedex);

    printf("    ... Calling detail_pokemon\n");
    detail_pokemon(pokedex);

    printf("    ... Destroying Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed detail_pokemon tests!\n");
}

// `test_print_pokemon` checks whether the print_pokemon function works
// correctly.
//
// It does this by creating the Pokemon Bulbasaur and Ivysaur, and
// calling print_pokemon to print out the names of the currently
// selected pokemon.
static void test_print_pokemon(void) {
    printf("\n>> Testing print_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Testing print_pokemon on an empty Pokedex\n");   
    print_pokemon(pokedex);

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(get_current_pokemon(pokedex) == bulbasaur);

    printf("    ... Calling print_pokemon\n");
    print_pokemon(pokedex);
    
    printf("    ... Setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);

    printf("    ... Calling print_pokemon\n");
    print_pokemon(pokedex);

    printf("    ... Calling next_pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Ivysaur\n");
    assert(get_current_pokemon(pokedex) == ivysaur);

    printf("    ... Calling print_pokemon\n");
    print_pokemon(pokedex);
    
    printf("    ... Setting Ivysaur to be found\n");
    find_current_pokemon(pokedex);

    printf("    ... Calling print_pokemon\n");
    print_pokemon(pokedex);

    printf("    ... Destroying Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed print_pokemon tests!\n");
}

////////////////////////////////////////////////////////////////////////
//                      Stage Two Testing                             //
////////////////////////////////////////////////////////////////////////


// `test_prev_and_next_pokemon` checks whether the next_pokemon and prev_pokemon 
// function works correctly.
//
// It does this by creating four Pokemon: Bulbasaur, Ivysaur, Mr Mime & Ditto. 
// It then adds these to the Pokedex, then checks that calling the
// prev_pokemon and next_pokemon functions changes the currently selected Pokemon.
static void test_prev_and_next_pokemon(void) {
    printf("\n>> Testing prev_pokemon and next_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Attempting to move to the prev pokemon when the pokedex is empty\n");
    prev_pokemon(pokedex);

    printf("    ... Attempting to move to the next pokemon when the pokedex is empty\n");
    next_pokemon(pokedex);

    printf("    ... Creating Bulbasaur and Ivysaur\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();

    printf("    ... Adding Bulbasaur and Ivysaur to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    printf("    ... Attempting to move to the prev pokemon when no previous exists\n");
    prev_pokemon(pokedex);

    printf("    ... Moving to the next pokemon\n");
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Ivysaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));

    printf("    ... Moving to the previous pokemon\n");
    prev_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    printf("    ... Creating Mr Mime and Ditto\n");
    Pokemon mrmime = create_mr_mime();
    Pokemon ditto = create_ditto();

    printf("    ... Adding Mr Mime and Ditto to the Pokedex\n");
    add_pokemon(pokedex, mrmime);
    add_pokemon(pokedex, ditto);

    printf("    ... Moving to the end of the list\n");
    next_pokemon(pokedex);
    next_pokemon(pokedex);
    next_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Ditto\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ditto));  

    printf("    ... Attempting to move to the next pokemon when no next exists\n");
    next_pokemon(pokedex);
    assert(is_same_pokemon(get_current_pokemon(pokedex), ditto)); 

    printf("    ... Moving to the previous pokemon\n");
    prev_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Mr Mime\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), mrmime));        

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed prev_pokemon and next_pokemon tests!\n");
}

// `test_change_and_remove_pokemon` checks whether the change_current_pokemon and
// remove_pokemon functions work correctly.
//
// It does this by creating four Pokemon: Bulbasaur, Ivysaur, Psyduck, Golduck. 
// It then adds these to the Pokedex, then checks that calling the
// remove_pokemon and change_current_pokemon will remove and change the current pokemon.
static void test_change_and_remove_pokemon(void) {
    printf("\n>> Testing remove_pokemon and change_current_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Attempting to remove pokemon when the pokedex is empty\n");
    remove_pokemon(pokedex);

    printf("    ... Attempting to move to pokemon id 1 when the pokedex is empty\n");
    change_current_pokemon(pokedex, 9);

    printf("    ... Creating Bulbasaur, Ivysaur, Psyduck and Golduck\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();
    Pokemon psyduck = create_psyduck();
    Pokemon golduck = create_golduck();

    printf("    ... Adding Bulbasaur, Ivysaur, Psyduck and Golduck to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    add_pokemon(pokedex, psyduck);
    add_pokemon(pokedex, golduck);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    printf("    ... Attempting to move pokemon id 100 where no pokemon exists\n");
    change_current_pokemon(pokedex, 100);
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    printf("    ... Moving to Golduck\n");
    change_current_pokemon(pokedex, 55);

    printf("       --> Checking that the current Pokemon is Golduck\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), golduck));

    printf("    ... Removing Golduck\n");
    remove_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Psyduck\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), psyduck));

    printf("    ... Moving to Ivysaur\n");
    change_current_pokemon(pokedex, 2);

    printf("       --> Checking that the current Pokemon is Ivysaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), ivysaur));  

    printf("    ... Removing Ivysaur\n");
    remove_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Psyduck\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), psyduck));     

    printf("    ... Removing Psyduck\n");
    remove_pokemon(pokedex);

    printf("       --> Checking that the current Pokemon is Bulbasaur\n");
    assert(is_same_pokemon(get_current_pokemon(pokedex), bulbasaur));

    printf("    ... Removing Bulbasaur\n");
    remove_pokemon(pokedex); 

    printf("    ... Destroying the Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed remove_pokemon and change_current_pokemon tests!\n");
}

////////////////////////////////////////////////////////////////////////
//                      Stage Three Testing                           //
////////////////////////////////////////////////////////////////////////
// `test_show_types` checks whether the show_types function works
// correctly.
//
// It does this by creating 6 pokemon, and calling show_types to print 
// out the types of the pokedex

static void test_show_types (void) {
    printf("\n>> Testing show_types\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Testing show_types on an empty Pokedex\n");   
    print_pokemon(pokedex);

    pokedex = build_pokedex_6(pokedex);

    printf("    ... Calling show_types\n");
    show_types(pokedex);
    
    printf("    ... Removing Bulbasaur and Ivysaur\n");
    remove_pokemon(pokedex);
    remove_pokemon(pokedex);

    printf("    ... Calling show_types\n");
    show_types(pokedex);

    printf("    ... Removing Psyduck and Golduck\n");
    remove_pokemon(pokedex);
    remove_pokemon(pokedex);

    printf("    ... Calling show_types\n");
    show_types(pokedex);

    printf("    ... Removing Exeggcute and Exeggutor\n");
    remove_pokemon(pokedex);
    remove_pokemon(pokedex);

    printf("    ... Calling show_types\n");
    show_types(pokedex);

    printf("    ... Destroying Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed show_types tests!\n");
}

// `test_go_exploring` checks whether the go_exploring function works
// correctly.
//
// It does this by creating the Pokemon Bulbasaur, Ivysaur, Psyduck, Golduck, 
// Exeggcute and Exeggutor and calls go_exploring twice. It then checks 
// thats the correct amount of pokemon have been found.
static void test_go_exploring (void) {
    printf("\n>> Testing go_exploring\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Attempting to explore when the pokedex is empty\n");
    go_exploring(pokedex);

    pokedex = build_pokedex_6 (pokedex);

    printf("    ... Calling go_exploring\n");
    go_exploring(pokedex);

    printf("       --> Checking that the correct pokemon were found");
    assert(count_found_pokemon(pokedex) == 3);

    printf("    ... Calling go_exploring again\n");
    go_exploring(pokedex);

    printf("       --> Checking that the correct pokemon were found");
    assert(count_found_pokemon(pokedex) == 6);

    printf("    ... Calling go_exploring when all pokemon are found\n");
    go_exploring(pokedex);

    printf("       --> Checking that the found pokemon remained the same");
    assert(count_found_pokemon(pokedex) == 6);

    printf("    ... Destroying Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed go_exploring tests!\n");

}

////////////////////////////////////////////////////////////////////////
//                     Stage Four Testing                             //
////////////////////////////////////////////////////////////////////////
// `test_evolutions` checks whether the stage 4 evolutions function works
// correctly. (add_pokemon_evolution, show_evolutions, get_next_evolution);
//
static void test_evolutions(void) {
    printf("\n>> Testing add_pokemon_evolution, show_evolutions and get_next_evolution\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    pokedex = build_pokedex_6 (pokedex);
    Pokemon venusaur = create_venusaur();
    add_pokemon(pokedex, venusaur);

    printf("    ... Calling show_evolutions when no evolutions have been added\n");
    show_evolutions(pokedex);

    printf("    ... Evolving Bulbasaur to Ivysaur\n");
    add_pokemon_evolution(pokedex, 1, 2);

    printf("       --> Checking that the evolution of Bulbasaur is Ivysaur");
    int id = get_next_evolution(pokedex);
    assert(id == 2);

    printf("       --> Showing the evolution of Bulbasaur");
    show_evolutions(pokedex);

    printf("    ... Evolving Ivysaur to Venusaur\n");
    add_pokemon_evolution(pokedex, 2, 3);

    printf("       --> Checking that Ivysaur's next evolution is Venusaur\n");
    next_pokemon(pokedex);
    id = get_next_evolution(pokedex);
    assert(id == 3);

    printf("       --> Showing the evolution of Bulbasaur");
    show_evolutions(pokedex);

    printf("    ... Destroying Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed add_pokemon_evolution, show_evolutions and get_next_evolution tests!\n");   

}

////////////////////////////////////////////////////////////////////////
//                     Stage Five Testing                             //
////////////////////////////////////////////////////////////////////////

// 'test_get_pokemon_of_type' tests whether get_pokemon_of_type function works
// correctly. 
//
// It does this by creating 7 pokemon and finding 2 types of each pokemon using 
// go_explore and checks whether the correct pokemon have been copied into the
// new pokedex.
static void test_get_pokemon_of_type(void) {
    printf("\n>> Testing get_pokemon_of_type\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    pokedex = build_pokedex_6 (pokedex);
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();
    Pokemon exeggcute = create_exeggcute();
    Pokemon exeggutor = create_exeggutor();

    printf("    ... Getting type fire Pokemon when none are of type fire\n");
    printf("       --> Checking the no Pokemon were copied and returned\n");
    assert(count_total_pokemon(get_pokemon_of_type(pokedex, FIRE_TYPE)) == 0);

    printf("    ... calling go_exploring twice to find 2 types of poison, water, psychic and grass pokemon\n");
    go_exploring(pokedex);
    go_exploring(pokedex);

    printf("    ... Getting all poison type Pokemon\n");
    Pokedex type_pokedex = get_pokemon_of_type(pokedex, POISON_TYPE);

    printf("       --> Checking that correct Pokemon were copied and returned\n");
    assert(count_total_pokemon(type_pokedex) == 2);
    assert(count_found_pokemon(type_pokedex) == 2);
    assert(is_copied_pokemon(get_current_pokemon(type_pokedex), bulbasaur));
    next_pokemon(type_pokedex);
    assert(is_copied_pokemon(get_current_pokemon(type_pokedex), ivysaur));

    printf("    ... Getting all psychic type Pokemon\n");
    type_pokedex = get_pokemon_of_type(pokedex, PSYCHIC_TYPE);

    printf("       --> Checking that correct Pokemon were copied and returned\n");
    assert(count_total_pokemon(type_pokedex) == 2);
    assert(count_found_pokemon(type_pokedex) == 2);
    assert(is_copied_pokemon(get_current_pokemon(type_pokedex), exeggcute));
    next_pokemon(type_pokedex);
    assert(is_copied_pokemon(get_current_pokemon(type_pokedex), exeggutor));

    printf("    ... Destroying Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed get_pokemon_of_type tests!\n");   


}

// `test_get_found_pokemon` checks whether the get_found_pokemon
// function works correctly.
//
// It does this by creating two Pokemon: Bulbasaur and Ivysaur (using
// the helper functions in this file and the provided code in pokemon.c).
//
// It then adds these to the Pokedex, sets Bulbasaur to be found, and
// then calls the get_found_pokemon function to get all of the Pokemon
// which have been found (which should be just the one, Bulbasaur).
static void test_get_found_pokemon(void) {
    printf("\n>> Testing get_found_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    printf("    ... Testing get_found_pokemon on an empty pokedex\n");
    assert(count_total_pokemon(get_found_pokemon(pokedex)) == 0);

    pokedex = build_pokedex_6 (pokedex);
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();
    Pokemon golduck = create_golduck();

    printf("    ... Getting found Pokemon when none are found\n");
    Pokedex found_pokedex = get_found_pokemon(pokedex);

    printf("       --> Checking the no Pokemon were added to the list\n");
    assert(count_total_pokemon(found_pokedex) == 0);
    assert(count_found_pokemon(found_pokedex) == 0);
    
    printf("    ... Setting Bulbasaur to be found\n");
    find_current_pokemon(pokedex);

    printf("    ... Getting all found Pokemon\n");
    found_pokedex = get_found_pokemon(pokedex);

    printf("       --> Checking the correct Pokemon were copied and returned\n");
    assert(count_total_pokemon(found_pokedex) == 1);
    assert(count_found_pokemon(found_pokedex) == 1);
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), bulbasaur));

    printf("    ... Setting Ivysaur and Golduck to be found\n");
    next_pokemon(pokedex);
    find_current_pokemon(pokedex);
    next_pokemon(pokedex);
    next_pokemon(pokedex);    
    find_current_pokemon(pokedex);
    assert(count_found_pokemon(pokedex) == 3);

    char *name1 = pokemon_name(get_current_pokemon(pokedex));
    printf("    ... Currently selected pokemon is %s\n", name1);

    printf("    ... Getting all found Pokemon\n");
    found_pokedex = get_found_pokemon(pokedex);   

    printf("       --> Checking the correct Pokemon were copied and returned\n");
    assert(count_total_pokemon(found_pokedex) == 3);
    assert(count_found_pokemon(found_pokedex) == 3);
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), bulbasaur)); 
    next_pokemon(found_pokedex);
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), ivysaur));
    next_pokemon(found_pokedex); 
    assert(is_copied_pokemon(get_current_pokemon(found_pokedex), golduck)); 

    prev_pokemon(found_pokedex);
    prev_pokemon(found_pokedex);

    printf("       --> Checking that the id's are ascending\n");
    int first_id = pokemon_id(get_current_pokemon(found_pokedex));
    next_pokemon(found_pokedex);
    int second_id = pokemon_id(get_current_pokemon(found_pokedex));
    next_pokemon(found_pokedex);
    int third_id = pokemon_id(get_current_pokemon(found_pokedex));       
    assert(first_id < second_id);
    assert(second_id < third_id);

    printf("       --> Checking that the currently selected pokemon in the original pokedex has not changed\n");
    char *name2 = pokemon_name(get_current_pokemon(pokedex));
    printf("    ... Currently selected pokemon is %s\n", name2);

    printf("    ... Destroying both Pokedexes\n");
    destroy_pokedex(pokedex);
    destroy_pokedex(found_pokedex);

    printf(">> Passed get_found_pokemon tests!\n");
}

// 'test_search_pokemon' tests whether search_pokemon function works
// correctly. 
//
// It does this by creating 7 pokemon and finding 2 types of each pokemon using 
// go_explore and checks whether the correct pokemon have been copied into the
// new pokedex.
static void test_search_pokemon(void) {
    printf("\n>> Testing search_pokemon\n");

    printf("    ... Creating a new Pokedex\n");
    Pokedex pokedex = new_pokedex();

    pokedex = build_pokedex_6 (pokedex);
    Pokemon exeggcute = create_exeggcute();
    Pokemon exeggutor = create_exeggutor();
    Pokemon psyduck = create_psyduck();
    Pokemon golduck = create_golduck();

    printf("    ... Searching for 'egg', when no pokemon have been found yet\n");
    printf("       --> Checking that no Pokemon were copied and returned\n");
    assert(count_total_pokemon(search_pokemon(pokedex, "egg")) == 0);

    printf("    ... calling go_exploring 3 times to find all pokemon\n");
    go_exploring(pokedex);
    go_exploring(pokedex);

    printf("    ... Searching for 'egg'\n");
    printf("       --> Checking that the correct Pokemon were copied and returned\n");
    Pokedex text_pokedex = search_pokemon(pokedex, "egg");
    assert(count_total_pokemon(text_pokedex) == 2);
    assert(is_copied_pokemon(get_current_pokemon(text_pokedex), exeggcute));
    next_pokemon(text_pokedex);
    assert(is_copied_pokemon(get_current_pokemon(text_pokedex), exeggutor));

    printf("    ... Searching for 'yeeeeehaw', which does not exist within the pokedex\n");
    printf("       --> Checking that no Pokemon were copied and returned\n");
    assert(count_total_pokemon(search_pokemon(pokedex, "yeeeeehaw")) == 0);

    printf("    ... Searching for 'duck'\n");
    text_pokedex = search_pokemon(pokedex, "duck");

    printf("       --> Checking the correct Pokemon were copied and returned\n");
    assert(count_total_pokemon(text_pokedex) == 2);
    assert(count_found_pokemon(text_pokedex) == 2);
    assert(is_copied_pokemon(get_current_pokemon(text_pokedex), psyduck));
    next_pokemon(text_pokedex);
    assert(is_copied_pokemon(get_current_pokemon(text_pokedex), golduck));

    printf("    ... Destroying Pokedex\n");
    destroy_pokedex(pokedex);

    printf(">> Passed search_pokemon tests!\n");   


}

////////////////////////////////////////////////////////////////////////
//                     Helper Functions                               //
////////////////////////////////////////////////////////////////////////

// Helper function to create Bulbasaur for testing purposes.
static Pokemon create_bulbasaur(void) {
    Pokemon pokemon = new_pokemon(
            BULBASAUR_ID, BULBASAUR_NAME,
            BULBASAUR_HEIGHT, BULBASAUR_WEIGHT,
            BULBASAUR_FIRST_TYPE,
            BULBASAUR_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Ivysaur for testing purposes.
static Pokemon create_ivysaur(void) {
    Pokemon pokemon = new_pokemon(
            IVYSAUR_ID, IVYSAUR_NAME,
            IVYSAUR_HEIGHT, IVYSAUR_WEIGHT,
            IVYSAUR_FIRST_TYPE,
            IVYSAUR_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create venusaur for testing purposes.
static Pokemon create_venusaur(void) {
    Pokemon pokemon = new_pokemon(
            VENUSAUR_ID, VENUSAUR_NAME,
            VENUSAUR_HEIGHT, VENUSAUR_WEIGHT,
            VENUSAUR_FIRST_TYPE,
            VENUSAUR_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Psyduck for testing purposes.
static Pokemon create_psyduck(void) {
    Pokemon pokemon = new_pokemon(
            PSYDUCK_ID, PSYDUCK_NAME,
            PSYDUCK_HEIGHT, PSYDUCK_WEIGHT,
            PSYDUCK_FIRST_TYPE,
            PSYDUCK_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Golduck for testing purposes.
static Pokemon create_golduck(void) {
    Pokemon pokemon = new_pokemon(
            GOLDUCK_ID, GOLDUCK_NAME,
            GOLDUCK_HEIGHT, GOLDUCK_WEIGHT,
            GOLDUCK_FIRST_TYPE,
            GOLDUCK_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Exeggcute for testing purposes.
static Pokemon create_exeggcute(void) {
    Pokemon pokemon = new_pokemon(
            EXEGGCUTE_ID, EXEGGCUTE_NAME,
            EXEGGCUTE_HEIGHT, EXEGGCUTE_WEIGHT,
            EXEGGCUTE_FIRST_TYPE,
            EXEGGCUTE_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create Exeggutor for testing purposes.
static Pokemon create_exeggutor(void) {
    Pokemon pokemon = new_pokemon(
            EXEGGUTOR_ID, EXEGGUTOR_NAME,
            EXEGGUTOR_HEIGHT, EXEGGUTOR_WEIGHT,
            EXEGGUTOR_FIRST_TYPE,
            EXEGGUTOR_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create mr mime for testing purposes.
static Pokemon create_mr_mime(void) {
    Pokemon pokemon = new_pokemon(
            MRMIME_ID, MRMIME_NAME,
            MRMIME_HEIGHT, MRMIME_WEIGHT,
            MRMIME_FIRST_TYPE,
            MRMIME_SECOND_TYPE
    );
    return pokemon;
}

// Helper function to create ditto for testing purposes.
static Pokemon create_ditto(void) {
    Pokemon pokemon = new_pokemon(
            DITTO_ID, DITTO_NAME,
            DITTO_HEIGHT, DITTO_WEIGHT,
            DITTO_FIRST_TYPE,
            DITTO_SECOND_TYPE
    );
    return pokemon;
}


// Helper function to compare whether two Pokemon are the same.
// This checks that the two pointers contain the same address, i.e.
// they are both pointing to the same pokemon struct in memory.
//
// Pokemon ivysaur = new_pokemon(0, 'ivysaur', 1.0, 13.0, GRASS_TYPE, POISON_TYPE)
// Pokemon also_ivysaur = ivysaur
// is_same_pokemon(ivysaur, also_ivysaur) == TRUE
static int is_same_pokemon(Pokemon first, Pokemon second) {
    return first == second;
}

// Helper function to compare whether one Pokemon is a *copy* of
// another, based on whether their attributes match (e.g. pokemon_id,
// height, weight, etc).
// 
// It also checks that the pointers do *not* match -- i.e. that the
// pointers aren't both pointing to the same pokemon struct in memory.
// If the pointers both contain the same address, then the second
// Pokemon is not a *copy* of the first Pokemon.
// 
// This function doesn't (yet) check that the Pokemon's names match
// (but perhaps you could add that check yourself...).
static int is_copied_pokemon(Pokemon first, Pokemon second) {
    return (pokemon_id(first) == pokemon_id(second))
    &&  (first != second)
    &&  (pokemon_height(first) == pokemon_height(second))
    &&  (pokemon_weight(first) == pokemon_weight(second))
    &&  (pokemon_first_type(first) == pokemon_first_type(second))
    &&  (pokemon_second_type(first) == pokemon_second_type(second));
}

// Helper Functions

Pokedex build_pokedex_6 (Pokedex pokedex) {

    printf("    ... Creating Bulbasaur, Ivysaur, Psyduck, Golduck, Exeggcute and Exeggutor\n");
    Pokemon bulbasaur = create_bulbasaur();
    Pokemon ivysaur = create_ivysaur();
    Pokemon psyduck = create_psyduck();
    Pokemon golduck = create_golduck();
    Pokemon exeggcute = create_exeggcute();
    Pokemon exeggutor = create_exeggutor();

    printf("    ... Adding Bulbasaur, Ivysaur, Psyduck, Golduck, Exeggcute and Exeggutor to the Pokedex\n");
    add_pokemon(pokedex, bulbasaur);
    add_pokemon(pokedex, ivysaur);
    add_pokemon(pokedex, psyduck);
    add_pokemon(pokedex, golduck);
    add_pokemon(pokedex, exeggcute);
    add_pokemon(pokedex, exeggutor);

    return pokedex; 
}
