//Ravela Smyth, CS 532, Project 1
//"Maze.java"

import java.io.*;
import java.util.*;

public class Maze{
    private Pairs internal_walls[];
    private UnionFind cells;
    private int SIZE;
    
    public Maze (int N) {
        SIZE = N;
        cells = new UnionFind(SIZE*SIZE);
        internal_walls = new Pairs[2*(SIZE*(SIZE-1))];

        fill_iw();
        random_iw(); 
        knock_iw();
    }
 
    private void fill_iw() {
        for (int x = 0, j=0 ; j < 2*(SIZE * (SIZE-1)) ; x++)    { 
                if ((x+1) % SIZE !=0) { internal_walls[j++] = new Pairs(x,x+1);}
                if (x+SIZE < SIZE*SIZE) {internal_walls[j++] = new Pairs(x,x+SIZE);}
        }
    }
   
    private void random_iw() {
        Random rand = new Random();

        for (int i = 0, r, holder; i < internal_walls.length ; i++){
            r = rand.nextInt(SIZE) % (i+1); 
        
            //swap x
            holder=internal_walls[i].getx(); 
            internal_walls[i].setx(internal_walls[r].getx()); 
            internal_walls[r].setx(holder);
    
            //swap y
            holder=internal_walls[i].gety(); 
            internal_walls[i].sety(internal_walls[r].gety()); 
            internal_walls[r].sety(holder);
        }
    }

    private void knock_iw() {
        for (int i =0; i < internal_walls.length; i++)  { 
           if (cells.pcFind(internal_walls[i].getx()) != cells.pcFind(internal_walls[i].gety())) {
              
                internal_walls[i].setKnock(true);
                cells.wUnion(internal_walls[i].getx(), internal_walls[i].gety());
            }            }
    }

    public void printKnock(){
          System.out.println("\nWalls for a " + SIZE + "x" + SIZE + " maze:");
          for (int i = 0 ; i < internal_walls.length; i++)
                System.out.println("(" + internal_walls[i].getx() + ","  + internal_walls[i].gety() + ") : " + (internal_walls[i].getKnock() ? "KNOCKED DOWN" : "LEFT UP"));
    }

       
    
}



