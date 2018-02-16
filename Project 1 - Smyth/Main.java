//Ravela Smyth, CS 532, Project 1
//"Main.java"

import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) {

        System.out.println("PART 1\n");
        UnionFind forest2 = new UnionFind(4);

		forest2.wUnion(0,1);
		forest2.wUnion(2,0);
		forest2.wUnion(3,0);
		forest2.printArray();

		UnionFind forest1 = new UnionFind(12);

		forest1.wUnion(0,1);
		forest1.wUnion(2,3);
		forest1.wUnion(4,5);
		forest1.wUnion(6,7);
		forest1.wUnion(8,9);
		forest1.wUnion(10,11);

		forest1.printArray();

		forest1.wUnion(0,3);
		forest1.wUnion(5,0);
		forest1.wUnion(6,9);
		forest1.printArray();

        forest1.wUnion(9,5);
		forest1.wUnion(5,11);  

        System.out.print("\n" + forest1.pcFind(9) + "\n");

		forest1.printArray();

        System.out.println("PART 2\n");
	}
}
