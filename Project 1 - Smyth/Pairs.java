//Ravela Smyth, CS 532, Project 1
//"Pairs.java"

import java.io.*;
import java.util.*;

public class Pairs {

    private int x,y;
    private boolean knock = false;
    
    //constructor
    public Pairs (int x, int y) {setx(x); sety(y);}

    //Accessor
    public int getx() {return x;}
    public int gety() {return y;}
    public boolean getKnock() {return knock;}

    //Mutator
    public void setx(int x) {this.x=x;};
    public void sety(int y) {this.y=y;};
    public void setKnock(boolean knock) {this.knock=knock;};


}
