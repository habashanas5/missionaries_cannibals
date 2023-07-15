package missionariescannibals;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Greedy {
    
    private int ml_count, cl_count, mr_count, cr_count;
    private boolean side;       // False = Left, True = Right
    private List <State> queue;
    private List <State> repeated;
    private List <State> solution;
    private Rules rules;
    
    public Greedy(int ml_count, int cl_count, int mr_count, int cr_count, boolean side) {
        this.ml_count = ml_count;
        this.cl_count = cl_count;
        this.mr_count = mr_count;
        this.cr_count = cr_count;
        this.side = side;
        side = false;
        queue = new ArrayList <> ();   // Open list
        repeated = new ArrayList <> (); // Closed list
        solution = new ArrayList <> (); // Solution
        rules = new Rules(ml_count, cl_count, mr_count, cr_count);
    }
    
    private void sort() {
//        System.out.println(queue);
        Collections.sort(queue, (s1, s2) -> s1.getHeuristic().compareTo(s2.getHeuristic()));
    }
    
    private boolean equals(State r, State s) {
        return (r.getSide() == s.getSide() && r.getCanNum() == s.getCanNum() && r.getMisNum() == s.getMisNum());
    }
    
    private void filter() {
        List <State> toRemove = new ArrayList <> ();
        boolean side = !solution.get(0).getSide();
        for(State s : solution) {
            if(s.getSide() == side)
                toRemove.add(s);
            side = s.getSide();
        }
        solution.removeAll(toRemove);
    }
    
    private void print() {
        for(State s : solution)
            System.out.println(s.toString());
    }

    public State runAlgorithm() {
        State init = new State(ml_count, cl_count, side, null);
        queue.add(init);
        solution.add(init);
        
        while(!queue.isEmpty()) {
            // Sort the open list
            sort();
            State current = queue.get(0);
            
//            System.out.print("\nCurrent State: ");
//            System.out.println(current.toString());
            
            if(!rules.isValidMove(current))
                return null;
            
            if(!rules.isGoal(current)) {
                ArrayList <State> children = new ArrayList <> ();
                if(current.getSide() == false) {   // If we are on the left side
                    children.add(new State(current.getMisNum()-1, current.getCanNum(), !current.getSide(), current));
                    children.add(new State(current.getMisNum()-2, current.getCanNum(), !current.getSide(), current));
                    children.add(new State(current.getMisNum(), current.getCanNum()-1, !current.getSide(), current));
                    children.add(new State(current.getMisNum(), current.getCanNum()-2, !current.getSide(), current));
                    children.add(new State(current.getMisNum()-1, current.getCanNum()-1, !current.getSide(), current));
                } else {    // If we are on the right side
                    children.add(new State(current.getMisNum()+1, current.getCanNum(), !current.getSide(), current));
                    children.add(new State(current.getMisNum()+2, current.getCanNum(), !current.getSide(), current));
                    children.add(new State(current.getMisNum(), current.getCanNum()+1, !current.getSide(), current));
                    children.add(new State(current.getMisNum(), current.getCanNum()+2, !current.getSide(), current));
                    children.add(new State(current.getMisNum()+1, current.getCanNum()+1, !current.getSide(), current));
                }
                Collections.sort(children, (s1, s2) -> s1.getHeuristic().compareTo(s2.getHeuristic()));
                
                for(State s : children) {
                    // If the state is valid and it is not in both closed and open list
                    boolean existInClosed = false;
                    boolean existInOpen = false;
                    for(State r : repeated)
                        if(equals(r, s))
                            existInClosed = true;
                    for(State r : queue)
                        if(equals(r, s))
                            existInOpen = true;
                    if(rules.isValidMove(s) && !existInClosed && !existInOpen) {

                        queue.add(s);
                        solution.add(s);
                        current.incrementCounter();
                    }
                }
                if(current.getPossibleChildrenCounter() == 0) {
                    State iterator = current;
                    while(iterator.getPossibleChildrenCounter() == 0) {
                        if(iterator == init)
                            break;
                        solution.remove(iterator);
                        iterator.getParent().decrementCounter();
                        iterator = iterator.getParent();
                    }
                }
                
                repeated.add(current);
                queue.remove(current);     // Retreive the current state if(repeated.indexOf(current) != -1)

            } else {
                filter();
                System.out.println("Solution size = " + solution.size() + " (Greedy) {\n");
                print();
                System.out.println("}\n");
                return current;
            }
        }
        return null;
    }
}