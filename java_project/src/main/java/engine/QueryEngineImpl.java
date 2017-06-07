package engine;

import li3.Interface;

import java.util.ArrayList;
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
        dataBase.addToTopContribs();
        dataBase.addToTopArtBytes();
        dataBase.addToTopArtWords();
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

        return this.dataBase.getTopContribuidores()
                                         .stream()
                                         .map(Contribuidor::getContributor_id)
                                         .limit(10)
                                         .collect(Collectors.toCollection(ArrayList::new));
    }

    public String contributor_name(long contributor_id) {
        try {
            return dataBase.getContributorNameByID(contributor_id);
        }
        catch (NullPointerException e){return null;}

    }

    public ArrayList<Long> top_20_largest_articles() {
             return this.dataBase.getTopArtBytes()
                    .stream()
                    .map(Artigo::getTitle_ID)
                    .limit(20)
                    .collect(Collectors.toCollection(ArrayList::new));
    }

    public String article_title(long article_id) {
        try {
            return dataBase.getArticleNameByID(article_id);
        }
        catch (NullPointerException e) {return null;}
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n) {

        return this.dataBase.getTopArtWords()
                .stream()
                .map(Artigo::getTitle_ID)
                .limit(n)
                .collect(Collectors.toCollection(ArrayList::new));

    }

    public ArrayList<String> titles_with_prefix(String prefix) {
        return this.dataBase.getMapArtigos().values()
                .stream()
                .filter(a -> a.getTitle().startsWith(prefix))
                .map(Artigo::getTitle)
                .sorted()
                .collect(Collectors.toCollection(ArrayList::new));

    }

    public String article_timestamp(long article_id, long revision_id) {
        try {
            return dataBase.getRevisionByID(article_id, revision_id);
        }
        catch (NullPointerException e) {return null;}
    }

    public void clean() {
        dataBase.getMapArtigos().clear();
        dataBase.getTopContribuidores().clear();
        dataBase.getTopContribuidores().clear();
        dataBase.getTopArtBytes().clear();
        dataBase.getTopArtWords().clear();

        dataBase = null;
        System.gc();
    }
}
