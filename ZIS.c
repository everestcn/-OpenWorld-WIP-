#include <stdio.h>

typedef struct Block_t Block_t;
typedef struct Item_t  Item_t;
typedef struct Ent_t   Ent_t;
typedef struct backpack backpack;
typedef struct map_item map_item;

struct map_item {
    int number;
    Item_t* itm;
    
};

struct Block_t {
    //l, r, f, b, u, d
    //struct Block_t* 3d_vex[ 6 ];
    struct map_item   items[ 25 ];
    struct Ent_t*   Ent[ 100 ];

    char bname;
    
    int bid;

};


struct Item_t {
    int m;
    char *name;
    char *introduce;
};

struct backpack {
    int max_m;
    int now_m;
    
    Item_t it[ 10 ];


};

Block_t map[ 5 ];

// 1
//02
// 34

Block_t **Simple_map[ 5 ][ 6 ] = {
    { (Block_t*[]){map+1,NULL}, (Block_t*[]){map+3,NULL}, (Block_t*[]){map+2,NULL}, NULL, NULL, NULL },
    { NULL, (Block_t*[]){map,map+2,NULL}, NULL, NULL, NULL, NULL },
    { (Block_t*[]){map+1,NULL}, (Block_t*[]){map+3,map+4,NULL}, NULL, (Block_t*[]){map,NULL}, NULL, NULL },
    { (Block_t*[]){map+2,NULL}, NULL, (Block_t*[]){map+4,NULL}, NULL, NULL, NULL },
    { (Block_t*[]){map+2,NULL}, NULL, NULL, (Block_t*[]){map+3,NULL}, NULL, NULL },
};


Item_t book = { 1, "Book", "Something for reading" };
Item_t table = { 5, "Table", "The most common wooden table" };
Item_t chair = { 3, "Chair", "Something for sitting" };



int main( void ) {
    int pid = 0;
    int way = -1;
    char c = 0;
    int nid = 0;
    
    printf( "\t假如学校爆发丧尸危机\n       \t\tver.beta\n\t(Working In Progress)\n(credit Tabclas)\n" );
    
    
    for ( int i = 0; i < 5; i++ ) {
        map[ i ].bname = 'A' + i, map[ i ].bid = i;
        
        map[ i ].items[ 0 ].number = 5;
        map[ i ].items[ 0 ].itm = ((struct Item_t*[]){ &book, &chair, &table })[ i % 3 ]; 
        
    }
            
    do {
    
        if ( c == '\n' ) continue;
        switch ( c ) {
            case 'L': way = 0; break;
            case 'R': way = 1; break;
            case 'F': way = 2; break;
            case 'B': way = 3; break;
            case 'U': way = 4; break;
            case 'D': way = 5; break;
            
            case 'C':
                for ( int i = 0; i < 25; i++ ) {
                    if ( !map[ pid ].items[ i ].itm ) break;
                    printf( "Item %s(%s) x %d(m:%dkg)\n", \
                    map[ pid ].items[ i ].itm->name, map[ pid ].items[ i ].itm->introduce, map[ pid ].items[ i ].number, \
                    map[ pid ].items[ i ].itm->m, map[ pid ].items[ i ].itm->m * map[ pid ].items[ i ].number );
                }
                
                break;
                
                
            default: break;
        }
        
        if ( ~way ) {
            scanf("%d",&nid);
            for ( int i = 0; ; i++ ) {
                if ( !Simple_map[pid][way][i] ) {
                    printf( "Invalid Number %d\n", nid );
                    break;
                }
                else {
                    if ( i == nid ) {
                        pid = Simple_map[pid][way][i]->bid;
                        break;
                    }
                }
            }
            
            nid = -1;
            way = -1;
        }
    
        printf( "At %c, places u can go:\n", map[ pid ].bname );
    
        for ( int i = 0; i < 6; i++ ) {
            if ( Simple_map[ pid ][ i ] != NULL ) {
                printf( "%c:", "LRFBUD"[i], i );
                for ( int j = 0; Simple_map[pid][i][j]; j++ ) {
                    printf( "%c, ", Simple_map[pid][i][j]->bname );
                }
                putchar( '\n' );
            }
        }
        
        
        
    } while ( ( c = getchar() ) != 'q' );
    

}


