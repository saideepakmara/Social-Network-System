/*
------------------------------------------------------------------------
                        THE SOCIAL NETWORK 
------------------------------------------------------------------------

The network allows users to create and manage different types of nodes.
Users can perform various actions within the social network.

STRUCTURE OF NODE:
-----------
    #  id  : Unique ID for each node.
    # name : Name of the node.
    # creation_date : Date of node creation.
    # type : Type of the node (Individual, Business, Group, Organisation).
    # birthday : Birthday of an Individual node (only for Individuals).
    # x, y : Location coordinates (only for Businesses).
    # set_of_postedContent : Linked list of content posted by the node.
    #  Multiple other array of linked lists to establish links with other nodes.
    # ownerOfIndex, customerOfIndex, memberOfIndex, ownerIndex, customerIndex, memberIndex: Indexes for links.

FUNCTIONS(AND THEIR FUNCTIONS):
---------------------
1. **search_ID:**
   Searches for a node by it's ID (By traversing through all the set of nodes).

2. **addBirthday:**
   Adds a birthday to an Individual node.

3. **addOwners:**
   Adds owners to Business node.
   By taking in the ID of individual it searches the node and create a double link between individual and business.

4. **addCustomers:**
   Adds customers to Business node.
   By taking in the ID of individual it searches the node and create a double link between individual and business.

5. **addGroupMembers:**
   Adds members to Group node.
   By taking in the ID of individual it searches the node and create a double link between individual and group.

6. **addOrganisationMembers:**
   Adds members to Organisation node.
   By taking in the ID of individual it searches the node and create a double link between individual and organisation.

7. **createNode:**
   Creates a new node based on user input.
   Initialisation of all data members by allocating the user input.

8. **deleteNode:**
   Deletes a node by it's ID.
   Deletes node by traversing through set of nodes list and updating the next pointer to delete the node.

9. **search:**
   Searches for nodes based on a specified attribute(Name, Type, Birthday{individual only}).
   Takes the input from user and sends the data to searchNode function.

10. **searchNode:**
    Acts as helper function for the search function.
    Traverses through the nodes and prints all the nodes based on user input.

11. **printbasedata:**
    Prints basic information of a node like Name, ID, Type.

12. **print1hop:**
    Prints information about 1-hop linked nodes of a given node.
    Based on type of node it prints the information from the links in input node.

13. **createAndPostContent:**
    Allows a user to create and post content for a node.
    Creates a linked list of contents (if more than one) and links to node via set of posted content.

14. **searchForContent:**
    Searches for content posted by any node within the network.\
    Simply traverses through the nodes and compares the input string and content strings.

15. **displayContentLinkedToIndividual:**
    Displays content posted by individuals linked to a given individual(via group/organisation).
    Uses loop-in-loop to traverse through all linked individuals of all groups the input individual is in and prints the content.

16. **printAllNodesInSystem:**
    Prints information about all nodes in the social network.
    Uses the set_of_nodes list and traverses through it to print all nodes and their information.

17. **menu:**
    Displays the main menu to provide options of task to do.

*/


#ifndef SOCIAL_H
#define SOCIAL_H

#define MAX_LINKS 10  // Maximum number of links (Owners, Customers, Members, Owner of businesses, Customer of businesses )

typedef struct Node {
    int id;
    char name[100];
    char creation_date[11];
    char type[20];
    char birthday[11]; //For individual 
    double x; //x-coordinate of location
    double y; //y-coordinate of location
    struct Node* set_of_postedContent;
    struct Node* next;

    struct Node* owners[MAX_LINKS]; // For Business
    struct Node* customers[MAX_LINKS]; // For Business
    struct Node* members[MAX_LINKS];  // For Group or Organization
    struct Node* customerOf[MAX_LINKS]; // For Individual
    struct Node* ownerOf[MAX_LINKS]; // For Individual
    struct Node* memberOf[MAX_LINKS]; //For Individual or Business

    // To keep track of Indexes for respective nodes
    int ownerOfIndex;
    int customerOfIndex;
    int memberOfIndex;
    int ownerIndex;
    int customerIndex;
    int memberIndex;

} Node;

Node* search_ID(int ID);
void addBirthday(Node* node, char* birthday);
void addOwners(Node* business, Node* individual);
void addCustomers(Node* business, Node* individual);
void addGroupMembers(Node* group);
void addOrganisationMembers(Node* organisation);
Node* createNode();
void deleteNode();
Node* searchNode(char attribute, char* value);
void search();
void printbasedata(Node* node);
void print1hop();
void createAndPostContent(Node* nodes);
void searchForContent(Node* nodes);
void displayContentLinkedToIndividual();
void printAllNodesInSystem(Node* nodes);
void menu();

#endif
