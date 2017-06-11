package engine;

import java.util.HashMap;
import java.util.TreeSet;
import java.util.function.Supplier;
import java.util.stream.Collectors;

public class Estruturas {

	private int unique_articles;
	private int all_articles;
	private int all_revisions;

	private HashMap<Long, Artigo> mapArtigos;
	private HashMap<Long, Contribuidor> mapContribuidores;
	private TreeSet<Contribuidor> topContribuidores;
	private TreeSet<Artigo> topArtBytes;
	private TreeSet<Artigo> topArtWords;

	public Estruturas(){
		unique_articles = 0;
		all_articles = 0;
		all_revisions = 0;
		mapArtigos = new HashMap<>();
		mapContribuidores = new HashMap<>();
		topContribuidores = new TreeSet<>();
		topArtBytes = new TreeSet<>();
		topArtWords = new TreeSet<>(new ComparatorArtigoWords());
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

	public HashMap<Long, Artigo> getMapArtigos() {
		return mapArtigos;
	}

	public Estruturas setMapArtigos(HashMap<Long, Artigo> mapArtigos) {
		this.mapArtigos = mapArtigos;
		return this;
	}

	public HashMap<Long, Contribuidor> getMapContribuidores() {
		return mapContribuidores;
	}

	public TreeSet<Contribuidor> getTopContribuidores() {
		return topContribuidores;
	}

	public Estruturas setTopContribuidores(TreeSet<Contribuidor> topContribuidores) {
		this.topContribuidores = topContribuidores;
		return this;
	}

	public TreeSet<Artigo> getTopArtBytes() {
		return topArtBytes;
	}

	public Estruturas setTopArtBytes(TreeSet<Artigo> topArtBytes) {
		this.topArtBytes = topArtBytes;
		return this;
	}

	public TreeSet<Artigo> getTopArtWords() {
		return topArtWords;
	}

	public Estruturas setTopArtWords(TreeSet<Artigo> topArtWords) {
		this.topArtWords = topArtWords;
		return this;
	}

	public void addToTopContribs(){
		this.topContribuidores = mapContribuidores.values()
				                                  .parallelStream()
												  .collect(Collectors.toCollection(TreeSet::new));
	}

	public void addToTopArtBytes(){
		this.topArtBytes = mapArtigos.values()
									 .parallelStream()
									 .collect(Collectors.toCollection(TreeSet::new));
	}

	public void addToTopArtWords() {
		Supplier<TreeSet<Artigo>> supplier =
				() -> new TreeSet<>(new ComparatorArtigoWords());

		this.topArtWords = mapArtigos.values()
									 .parallelStream()
									 .collect(Collectors.toCollection(supplier));
	}

	public Estruturas setMapContribuidores(HashMap<Long, Contribuidor> mapContribuidores) {
		this.mapContribuidores = mapContribuidores;
		return this;
	}

	public void addInfo(Artigo article, Contribuidor contributor){
		long article_id = article.getTitle_ID();
		boolean sameRevision = false;

		Artigo old_article = mapArtigos.get(article_id);
		if(old_article == null){
			mapArtigos.put(article_id, article);
			this.unique_articles++;
			this.all_revisions++;
		}
		else{
			if(! article.getNewestRevision().compare(old_article.getNewestRevision())){
				int maxLength = (article.getN_bytes() >= old_article.getN_bytes()) ?
						article.getN_bytes() : old_article.getN_bytes();
				int maxWords = (article.getN_words() >= old_article.getN_words()) ?
						article.getN_words() : old_article.getN_words();
				article.setN_bytes(maxLength);
				article.setN_words(maxWords);
				article.insertOldRevisions(old_article.getRevisoes());
				mapArtigos.replace(article_id, article);
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
				    old_contributor.addContributions_number();
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
