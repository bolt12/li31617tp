package engine;

import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

class Words extends RecursiveTask<Integer> {
    static final int SEQUENTIAL_THRESHOLD = 5000;

    int low;
    int high;
    String string;

    Words(String string, int lo, int hi) {
        this.string = string;
        low   = lo;
        high  = hi;
    }

    protected Integer compute() {
        if(high - low <= SEQUENTIAL_THRESHOLD) {
            int wordCount = 0;
            boolean word = false;
            int endOfText = high - 1;
            
            for(int i=low; i < high; ++i){

    			// Se estivermos numa letra, word = true.
    			if (!Character.isWhitespace(string.charAt(i)) && i != endOfText) {
    				word = true;
    				// Se não estivermos numa letra mas viermos de uma letra,
    				// acrescentamos ao contador.
    			} else if (Character.isWhitespace(string.charAt(i)) && word) {
    				wordCount++;
    				word = false;
    				// Se o ultimo caracter for uma letra
    			} else if (!Character.isWhitespace(string.charAt(i)) && i == endOfText) {
    				wordCount++;
    			}
    		}
            return wordCount;
         } else {
            int mid = low + (high - low) / 2;
            Words left  = new Words(string, low, mid);
            Words right = new Words(string, mid, high);
            left.fork();
            int rightAns = right.compute();
            int leftAns  = left.join();
            return leftAns + rightAns;
         }
     }

     static int numWords(String s) {
         return ForkJoinPool.commonPool().invoke(new Words(s, 0, s.length()));
     }
}