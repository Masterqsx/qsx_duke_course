package thehackers.smartbuy.gui;

import java.io.IOException;
import java.util.ArrayList;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class AmazonDetailCrawler {
	private Document productPage;
	private Document iFramePage;
	
	AmazonDetailCrawler(String productPageURL, String iFrameURL, String user_agent1, String user_agent2) {
		try {
			this.productPage = Jsoup.connect(productPageURL).timeout(30000).userAgent(user_agent1).get();
			this.iFramePage = Jsoup.connect(iFrameURL).timeout(30000).userAgent(user_agent2).get();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public float getMostUseFulRating() {
		Elements usefulRatings = this.productPage.select("div#revMH")
				.select("a.a-link-normal.a-text-normal.a-color-base")
				.select("span.a-icon-alt");
		float sum = 0;
		int total = usefulRatings.size();
		if (total == 0) return 0;
		for (Element el : usefulRatings) {
			try {
				sum += Float.parseFloat(el.text().split(" ", 2)[0]);
			} catch (java.lang.NumberFormatException e) {}
		}
		return sum / total;
	}
	
	public float getMostRecentRating() {
		Elements recentRatings = this.productPage.select("div#revMRRL")
				.select("a.a-link-normal.a-text-normal")
				.select("span.a-icon-alt");
		float sum = 0;
		int total = recentRatings.size();
		if (total == 0) return 0;
		for (Element el : recentRatings) {
			try {
				sum += Float.parseFloat(el.text().split(" ", 2)[0]);
			} catch (java.lang.NumberFormatException e) {}
		}
		return sum / total;
	}
	
	public ArrayList getReviews() {
		ArrayList contentList = new ArrayList();
		
		// Extract corresponding ratings
		Elements ratings = this.iFramePage.select("div[style=margin-bottom:0.5em;]")
				.select("img");
		
		// Extract titles
		Elements titles = this.iFramePage
				.select("div[style=margin-bottom:0.5em;]:has(span[style=margin-left: -5px;)")
				.select("b");

		// Extract reviews
		Elements reviews = this.iFramePage.select("div.crIframeReviewList")
				.select("div.reviewText");
		
		for (int i = 0; i < titles.size(); i++) {
			float rating = 0;
			try {
				rating = Float.parseFloat(ratings.get(i).attr("alt").split(" ", 2)[0]);
			} catch (java.lang.NumberFormatException e) {
			}
			contentList.add(new ReviewContent(titles.get(i).text(),
					reviews.get(i).text(), rating)
					);
		}
		
		return contentList;
	}
	
}
