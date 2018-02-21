//Ravela Smyth, CS 532, Project 1
//"Maze.java"

import java.io.*;
import java.util.*;
        
public class Maze{
    private Pairs walls[];
    private UnionFind cells;
    private int SIZE;

    class Pairs {
        private int x,y;
        private boolean knock;

        public Pairs (int x, int y) {this.x=x; this.y=y; this.knock=false;}
    }    

    public Maze (int N) {
        SIZE = N;
        cells = new UnionFind(SIZE*SIZE);
        walls = new Pairs[2*(SIZE*(SIZE-1))];

        fill_wall();
        random_wall(); 
        knock_wall();
    }
 
    private void fill_wall() {
        for (int x = 0, j=0 ; j < 2*(SIZE * (SIZE-1)) ; x++)    { 
                if ((x+1) % SIZE !=0) { walls[j++] = new Pairs(x,x+1);}
                if (x+SIZE < SIZE*SIZE) {walls[j++] = new Pairs(x,x+SIZE);}
        }
    }
   
    private void random_wall() {
        Random rand = new Random();

        for (int i = 0, r, holder; i < walls.length ; i++){
            r = rand.nextInt(SIZE) % (i+1); 
        
            //swap x
            holder = walls[i].x; 
            walls[i].x = walls[r].x; 
            walls[r].x = holder;
    
            //swap y
            holder = walls[i].y; 
            walls[i].y = walls[r].y; 
            walls[r].y = holder;
        }
    }

    private void knock_wall() {
        for (int i =0; i < walls.length; i++)  { 
           if (cells.pcFind(walls[i].x) != cells.pcFind(walls[i].y)) {            
                walls[i].knock = true;
                cells.wUnion(walls[i].x, walls[i].y);
            }            
        }
    }

    public void printKnock(){
          System.out.println("\nWalls for a " + SIZE + "x" + SIZE + " maze:");
          for (int i = 0 ; i < walls.length; i++)
                System.out.println("(" + walls[i].x + ","  + walls[i].y + ") : " + (walls[i].knock ? "KNOCKED DOWN" : "LEFT UP"));
    }
       
    
}




