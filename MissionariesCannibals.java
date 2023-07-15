package missionariescannibals;

import java.util.Scanner;

public class MissionariesCannibals {

    private static Scanner scanner;
    private static MissionariesCannibals game;

    public MissionariesCannibals() {
        scanner = new Scanner(System.in);
    }

    public static void main(String[] args) {
        game = new MissionariesCannibals();
        
        int ml_count, cl_count, mr_count, cr_count;
        String side;
        
        System.out.println("Enter the number of M's on the left side of the river: ");
        ml_count = scanner.nextInt();
        System.out.println("Enter the number of C's on the left side of the river: ");
        cl_count = scanner.nextInt();
        System.out.println("Enter the number of M's on the right side of the river: ");
        mr_count = scanner.nextInt();
        System.out.println("Enter the number of C's on the right side of the river: ");
        cr_count = scanner.nextInt();
        System.out.println("Enter the initial position of the boat: ");
        side = scanner.next();
        System.out.println("*****************************************************\n");
        
        State bfs = null;
        State greedy = null;
        if(side.equals("L")) {
            if(ml_count + cl_count == 0) {
                System.out.println("Invalid position of the boat");
                System.exit(0);
            }
            bfs = new BreadthFirstSearch(ml_count, cl_count, mr_count, cr_count, false).runAlgorithm();
            greedy = new Greedy(ml_count, cl_count, mr_count, cr_count, false).runAlgorithm();
        } else if(side.equals("R")) {
            if(mr_count + cr_count == 0) {
                System.out.println("Invalid position of the boat");
                System.exit(0);
            }
            bfs = new BreadthFirstSearch(ml_count, cl_count, mr_count, cr_count, true).runAlgorithm();
            greedy = new Greedy(ml_count, cl_count, mr_count, cr_count, true).runAlgorithm();
        }
        if(bfs != null) {
            System.out.println("The goal was reached by BREADTH FIRST SEARCH: ");
            System.out.println(bfs.toString());
        } else {
            System.out.println("No Solution by breadth first search algorithm");
        }
        if(greedy != null) {
            System.out.println("The goal was reached by BEST FIRST SEARCH (GREEDY): ");
            System.out.println(greedy.toString());
        } else {
            System.out.println("No Solution by greedy algorithm");
        }
    }

}
