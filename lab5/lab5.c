#include "lab5.h"

// ========================================================
// Function Declarations
// ========================================================
void delete_node(Vnode* station, char* vertex);
void visit_node(Graph* gr, Vnode* curr_node);
Vnode* get_station_from_edge_name(Graph* gr, char* edge_name);
void init_for_plan_route(Graph* gr, char* start);
Vnode* get_next_node_to_visit(Graph* gr);
char** get_route(Graph* gr, char* dest);


// ========================================================
// Lab 5 Functions
// ========================================================
char **plan_route(Graph *gr, char *start, char *dest){
    Vnode* curr_node = NULL;

    init_for_plan_route(gr, start);
    curr_node = get_next_node_to_visit(gr);
    while(curr_node){
        visit_node(gr, curr_node);
        curr_node = get_next_node_to_visit(gr);
    }

    return get_route(gr, dest);
    // Find next node to visit: Determine lowest cost, unvisted node
    // When visiting a node, for each of its neighbours:
        // If the new cost is lower, then
        // -- update cost
        // -- change prev node to be the currently visted node
}


void add(Graph *gr, char *station){
    // Check if station is already in graph
    for (int i = 0; i<gr->count; i++){
        if (strcmp(gr->adj_list[i]->station, station) == 0){
            return;
        }
    }
    
    // If station not in graph:    
    Vnode* new_node = malloc(sizeof(Vnode));
    strcpy(new_node->station, station);
    new_node->edges = NULL;
    
    // Make room in the adj list for a new node
    gr->adj_list = realloc(gr->adj_list, (gr->count + 1) * sizeof(Vnode*));
    gr->adj_list[gr->count] = new_node;
    gr->count++;
}


void update(Graph *gr, char *start, char *dest, int weight){
    // Adds vertex to graph if not already in graph
    add(gr, start);
    add(gr, dest);

    int found_edge = 0; // Default is that an edge does not exist b/w start and dest
    
    // Initialize nodes
    Enode* curr_edge = NULL;
    Vnode* Vstart = NULL;
    
    // Find start station in graph
    for (int i = 0; i<gr->count; i++){
        if (strcmp(gr->adj_list[i]->station, start) == 0){
            // Found the starting vertex
            Vstart = gr->adj_list[i];
            break;
        }
    }

    // Weight is 0: Delete existing edge or do nothing
    if (weight == 0){
        delete_node(Vstart, dest);
        return; // Starting node has no edges or connection b/w start & dest not found   
    }
    
    // Weight is not 0 --> create new edge or update existing edge
    else{ 
        curr_edge = Vstart->edges;
        while (curr_edge){
            if (strcmp(curr_edge->vertex, dest) == 0){
                found_edge = 1;
                break;
            }
            else if (curr_edge->next == NULL){
                break; // Iterated through entire LL, did not find edge
            }
            else{
                curr_edge = curr_edge->next; // Iterate to next edge
            }
        }

        // curr_edge will either be:
        // the edge connecting start to dest (found_edge = 1)
        // the last edge in the LL (found_edge = 0)

        if (found_edge == 0){
            Enode* new_edge = malloc(sizeof(Enode));
            new_edge->weight = weight;
            strcpy(new_edge->vertex, dest);
            new_edge->next = NULL;
            
            if (Vstart->edges == NULL){ // Node has no edges
                Vstart->edges = new_edge;
            }
            else{
                curr_edge->next = new_edge;
            }
        }

        else{ // found_edge != 0
            curr_edge->weight = weight;
        }
    }
}


void disrupt(Graph *gr, char *station){
    Vnode* Vdelete = NULL;
    Enode* curr_edge = NULL;
    int delete_idx = 0;

    for (int i = 0; i<gr->count; i++){
        if (strcmp(gr->adj_list[i]->station, station) == 0){
            // Found the station to be removed
            Vdelete = gr->adj_list[i];
            delete_idx = i;
            break;
        }
    }

    if (Vdelete){ // Make sure that <station> to be deleted is in graph
        // Delete all edges coming from Vdelete
        while (Vdelete->edges){
            delete_node(Vdelete, Vdelete->edges->vertex);                
        }
        
        // Delete all edges with Vdelete as the destination (vertex)
        for (int i = 0; i<gr->count; i++){
            curr_edge = gr->adj_list[i]->edges;
            while (curr_edge){
                if (strcmp(Vdelete->station, curr_edge->vertex) == 0){
                    delete_node(gr->adj_list[i], Vdelete->station);
                    break;
                }
                curr_edge = curr_edge->next;
            }
        }

        // Remove Vdelete from list of stations (adj_list)
        free(Vdelete);        
        for (int j = delete_idx; j<(gr->count)-1; j++){
            gr->adj_list[j] = gr->adj_list[j+1];
        }
        gr->count--;
    }

    if (gr->count == 0){
        free(gr->adj_list);
        gr->adj_list = NULL;
    }
}


// ========================================================
// Helper Functions
// ========================================================
void delete_node(Vnode* station, char* vertex){
    // Does nothing if <station> is not connected to <vertex>
    if (station->edges){
        if (strcmp(station->edges->vertex, vertex) == 0){
            Enode* delete_node = station->edges;
            station->edges = station->edges->next;
            free(delete_node);
        }
        else{
            Enode* curr = station->edges;
            while(curr->next){
                if (strcmp(curr->next->vertex, vertex) == 0){
                    Enode* delete_node = curr->next;
                    curr->next = delete_node->next;
                    free(delete_node);
                }
                else{
                    curr = curr->next;
                }
            }
        }
    }
}


void init_for_plan_route(Graph* gr, char* start){
    for (int i = 0; i<gr->count; i++){
        if (strcmp(gr->adj_list[i]->station, start) == 0){
            gr->adj_list[i]->cost = 0;
            gr->adj_list[i]->visited = 0;
            gr->adj_list[i]->prev = NULL;
        }
        else{
            gr->adj_list[i]->cost = 2147483647;
            gr->adj_list[i]->visited = 0;
            gr->adj_list[i]->prev = NULL;
        }
    }
}


Vnode* get_station_from_edge_name(Graph* gr, char* edge_name){
    Vnode* station = NULL;

    for (int i = 0; i<gr->count; i++){
        if (strcmp(gr->adj_list[i]->station, edge_name) == 0){
            station = gr->adj_list[i];
            break;
        }
    }
    return station;
}


void visit_node(Graph* gr, Vnode* curr_node){
    Enode* edge = curr_node->edges;
    Vnode* station = NULL;
    int temp_cost = 0;
    
    // Update the cost (and prev) of neighbouring nodes, if necessary
    while(edge){
        station = get_station_from_edge_name(gr, edge->vertex);
        temp_cost = curr_node->cost + edge->weight;
        if (temp_cost < station->cost){
            station->cost = curr_node->cost + edge->weight;
            station->prev = curr_node;
        }
        edge = edge->next;
    }
    // Node has been visited
    curr_node->visited = 1;
}


Vnode* get_next_node_to_visit(Graph* gr){
    int min_cost = 2147483647;
    Vnode* min_cost_node = NULL;

    for (int i = 0; i<gr->count; i++){
        // Only check through nodes that have not been visited
        if ((gr->adj_list[i]->visited == 0) && (gr->adj_list[i]->cost < min_cost)){
            min_cost = gr->adj_list[i]->cost;
            min_cost_node = gr->adj_list[i];
        }
    }
    return min_cost_node;
}


char** get_route(Graph* gr, char* dest){  
    int num_nodes = 0;
    Vnode* curr = get_station_from_edge_name(gr, dest);

    if (curr->cost == 2147483647){
        return NULL; // No path was found to the destination if the cost has not been updated
    }

    while(curr){
        num_nodes++;
        curr = curr->prev;
    }

    int idx = 0;
    char** route = malloc(sizeof(char*) * num_nodes);
    curr = get_station_from_edge_name(gr, dest);
    while(curr){
        route[idx] = strdup(curr->station);
        curr = curr->prev;
        idx++;
    }
    return route;
}
