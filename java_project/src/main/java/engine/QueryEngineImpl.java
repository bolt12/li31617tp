package engine;

import li3.Interface;

import java.util.ArrayList;
import java.util.TreeMap;
import java.util.stream.Collectors;

public class QueryEngineImpl implements Interface {
	
	private Estruturas dataBase;

    public void init() {
    	dataBase = new Estruturas();
    }

    public void load(int nsnaps, ArrayList<String> snaps_paths) {
    	Parsing parser = new Parsing();
    	for(int i = 0; i < nsnaps; i++){
    		parser.openXML(snaps_paths.get(i), dataBase);
    	}
    }

    public long all_articles() {

        return dataBase.getAll_articles();
    }

    public long unique_articles() {

        return dataBase.getUnique_articles();
    }

    public long all_revisions() {

        return dataBase.getAll_revisions();
    }

    public ArrayList<Long> top_10_contributors() {

        TreeMap<Contribuidor, Long> c = new TreeMap<>();
        for (Contribuidor c1 :
                this.dataBase.getMapContribuidores().values()) {
            c.put(c1, c1.getContributor_id());
        }
        ArrayList<Long> r = c.values().stream().limit(10).collect(Collectors.toCollection(ArrayList::new));
        return r;
    }

    public String contributor_name(long contributor_id) {

        return dataBase.getContributorNameByID(contributor_id);
    }

    public ArrayList<Long> top_20_largest_articles() {


        return new ArrayList<Long>();
    }

    public String article_title(long article_id) {

        return dataBase.getArticleNameByID(article_id);
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n) {

        return new ArrayList<Long>();
    }

    public ArrayList<String> titles_with_prefix(String prefix) {

        return new ArrayList<String>();
    }

    public String article_timestamp(long article_id, long revision_id) {

        return dataBase.getRevisionByID(article_id, revision_id);
    }

    public void clean() {

    }
}
