package engine;

import java.util.HashMap;

public class Estruturas {
	
	private HashMap<Long,Artigo> mapArtigos;
	private HashMap<Long, Contribuidor> mapContribuidores;
	
	public Estruturas(){
		mapArtigos = new HashMap<Long, Artigo>();
		mapContribuidores = new HashMap<Long,Contribuidor>();
	}
	
	
	public void addInfo(Artigo article, Contribuidor contributor){
		long article_id = article.getTitle_ID();
		long contributor_id = contributor.getContributor_id();
		mapArtigos.put(article_id, article);
		mapContribuidores.put(contributor_id, contributor);
		
	}
}
