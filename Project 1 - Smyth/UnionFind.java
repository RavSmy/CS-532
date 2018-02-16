//Ravela Smyth, CS 532, Project 1
//"UnionFind.java"

import java.io.*;
import java.util.*;

public class UnionFind
{
	//private:
	private int[] parent;

	//public:
	public UnionFind (int n) {
		parent = new int[n];
		Arrays.fill(parent, -1);
	}

	public void wUnion(int e1, int e2){
		int r1 = pcFind(e1);
		int r2 = pcFind(e2);

		if (r1 != r2){
			if (nodeCount(r1) > nodeCount(r2)) {parent[r2] = r1;}
			else {parent[r1] = r2;}
			}
		}

	public int nodeCount(int e) {
		int count = 0;
		for (int i = 0 ; i < parent.length; i++) if (parent[i] != -1 && pcFind(parent[i]) == e) count++;
		return count;
		}

	public int pcFind (int e) {
		if (parent[e] != -1 ) {
			parent[e] = pcFind(parent[e]);
			return parent[e];
			}

		return e;
	}

	public void printArray() {
		for (int i = 0 ; i < parent.length; i++) System.out.println(i + " : " + parent[i]);
	}


}
