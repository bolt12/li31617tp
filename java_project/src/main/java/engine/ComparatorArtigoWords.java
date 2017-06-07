package engine;

import java.util.Comparator;

public class ComparatorArtigoWords implements Comparator<Artigo> {

    public int compare(Artigo a1, Artigo a2){
        if(a1.getN_words()<a2.getN_words())
            return 1;
        else if(a1.getN_words()>a2.getN_words())
            return -1;
        else{
            if(a1.getTitle_ID()<a2.getTitle_ID())
                return -1;
        }
        return 1;

    }
}
