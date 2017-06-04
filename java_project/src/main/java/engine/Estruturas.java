package engine;

import java.util.HashMap;

public class Estruturas {
	
	private int unique_articles;
	private int all_articles;
	private int all_revisions;
	
	private HashMap<Long,Artigo> mapArtigos;
	private HashMap<Long, Contribuidor> mapContribuidores;
	
	public Estruturas(){
		unique_articles = 0;
		all_articles = 0;
		all_revisions = 0;
		mapArtigos = new HashMap<Long, Artigo>();
		mapContribuidores = new HashMap<Long,Contribuidor>();
	}
	
	public int getUnique_articles() {
		return unique_articles;
	}

	public int getAll_articles() {
		return all_articles;
	}

	public int getAll_revisions() {
		return all_revisions;
	}

	public void addInfo(Artigo article, Contribuidor contributor){
		long article_id = article.getTitle_ID();
		Boolean sameRevision = false;
		
		Artigo old_article = mapArtigos.get(article_id);
		if(old_article == null){
			mapArtigos.put(article_id, article);
			this.unique_articles++;
			this.all_revisions++;
		}
		else{
			if(! article.getNewestRevision().compare(old_article.getNewestRevision())){
				article.insertOldRevisions(old_article.getRevisoes());
				mapArtigos.put(article_id, article);
				this.all_revisions++;
			} else
				sameRevision = true;
		}
		this.all_articles++;
		
		if(!sameRevision)
			if(!contributor.isIP()){
				long contributor_id = contributor.getContributor_id();
				Contribuidor old_contributor = mapContribuidores.get(contributor_id);
				if(old_contributor == null)
					mapContribuidores.put(contributor_id, contributor);
				else{
					contributor.setContributions_number(old_contributor.getContributions_number() + 1);
				}
			}
	}
	
	public String getContributorNameByID(long contributor_id){
		return mapContribuidores.get(contributor_id).getContributor_name();
	}
	
	public String getArticleNameByID(long article_id){
		return mapArtigos.get(article_id).getTitle();
	}
	
	public String getRevisionByID(long article_id, long revision_id){
		return mapArtigos.get(article_id).getRevisionTimestampByID(revision_id);
	}
}
