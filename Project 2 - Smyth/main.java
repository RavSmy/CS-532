// Ravela Smyth, CS 532, Project 2
//main.java

import java.io.*;
import java.util.*;

public class main {

    public static void main(String[] args) {

        Queue<Node> min_pq = new PriorityQueue<>();
        Node root = null;
        
        // File Input
        try {

            Scanner input = new Scanner(new File("input.txt"));
            
            // Adding c:f into min_PQ 
            while (input.hasNext()) {
                min_pq.add(new Node(input.next().charAt(0), input.nextInt()));
            }

        }catch(Exception e){
            System.out.println("Didn't work, sorry: " + e);
            System.exit(0); 
            }

        // Constructing Huffman Tree 
        while(min_pq.size() != 1){  
            Node internal = new Node('\0', 0);
            internal.left = min_pq.remove();
            internal.right = min_pq.remove();

            internal.x = internal.left.x + internal.right.x; 

            root = internal; 
            min_pq.add(root);
        }
         
    
        // Decode and Print Huffman Tree
        genCode(root, ""); 
        printCode(root); 
        System.out.println("Lavg = " +  getBits(root, 0)/getFreq(root,0));
        System.out.println("CR = " + ((8 - getBits(root, 0)/getFreq(root,0))/ 8) );
          
    } 

    static void genCode(Node root, String str){
        if (root==null) return;
        if (root.c != '\0') root.huffcode = str;
        genCode(root.left, str+"0");
        genCode(root.right, str+"1");
    }
    
    // Calculating Lavg and Compression Rate
    static void printCode(Node root){
        if (root==null) return;
        if (root.c != '\0') System.out.println(root.c + "\t" + root.x + "\t" + root.huffcode);
        printCode(root.left);
        printCode(root.right);
    }

    static double getBits(Node root, int bits){
        if (root.c != '\0') return bits += (root.x * root.huffcode.length());  
        return getBits(root.left, bits) + getBits(root.right, bits);
       
    }

    static double getFreq(Node root, int freq){
        if (root.c != '\0') return freq += root.x;  
        return getFreq(root.left, freq) + getFreq(root.right, freq);
       
    }
 

} 



class Node implements Comparable<Node>
{
    int x;
    char c;
    String huffcode; 

    Node left;
    Node right;
    Node(char c, int x) { this.x = x; this.c=c; left = null; right = null; } 

    @Override
    // To change to a max heap, swap the 1 and -1 below
	public int compareTo(Node n) {
		if (this.x == n.x) return 0;
		if (this.x < n.x) return -1;
		return 1;		
	}

}
