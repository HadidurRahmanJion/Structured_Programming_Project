//*******************************************************************
//** Title   : Paths_Containing_All_The_Nodes_Having_Visas
//** Author  : Hadidur Rahman Jion, Undergraduate student, Khulna University
//*******************************************************************

#include <stdio.h>
#include <stdbool.h>

// Structure to represent a node in the tree
struct Node {
    int nodeid;         // Node ID
    int adjcount;       // Number of adjacent nodes
    int adjs[10];       // Array to store adjacent node IDs
    int costs[10];      // Array to store costs associated with each adjacent node
};

// Function to add a node to the tree
int addNode(struct Node *p, int nid, int count) {
    int i = 0, ncount = count;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid) {
            break;
        }
    }
    if (i == count) {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

// Function to add an adjacent node to a given node
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count) {
    int i = 0;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;
            break;
        }
    }
}

// Function to check if a node is already in the list
int added(int *list, int lcount, int nid) {
    int i = 0;
    for (i = 0; i < lcount; i++) {
        if (list[i] == nid) {
            return 1;
        }
    }
    return 0;
}

// Function to find paths containing all nodes having visas
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount) {
    int index = 0;

    if (list[lcount - 1] == end) {
        // Potential path found
        bool flag = true;
        for (int i = 1; i < lcount; i++) {
            bool flag2 = true;
            for (int j = 0; j < size; j++) {
                if (list[i] == visas[j]) {
                    flag2 = false;
                    break;
                } 
            }
            if (flag2) {
                flag = false;
                break;
            }
        }
        if (flag) {
            int tcost = 0;
            printf("\n");
            for (int i = 0; i < lcount; i++) {
                printf(" %d ", list[i]);
                tcost += clist[i];
            }
            printf(" cost = %d", tcost);
        }
        return;
    }

    for (int i = 0; i < count; i++) {
        if (p[i].nodeid == start) {
            index = i;
            break;
        }
    }

    for (int i = 0; i < p[index].adjcount; i++) {
        int a = added(list, lcount, p[index].adjs[i]);
        if (a == 0) {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath(p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

int main() {

    // Array to store nodes
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;

    // Input node connections and costs
    while (1) {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9) {
            break;
        }
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);

        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }

    // Input start and end nodes
    int start, end, n;
    printf("start, end ? ");
    scanf("%d %d", &start, &end);

    // Input visas
    printf("Enter the visas (Enter -9 to complete): ");
    while (1) {
        scanf("%d", &n);
        if (n == -9)
            break;
        visas[size++] = n;
    }

    // Initialize list for paths
    int list[50], clist[50], lcount = 1;
    list[0] = start;
    clist[0] = 0;

    // Find paths containing all nodes having visas
    findpath(nodes, nodecount, start, end, list, clist, lcount);

    return 0;
}
           
