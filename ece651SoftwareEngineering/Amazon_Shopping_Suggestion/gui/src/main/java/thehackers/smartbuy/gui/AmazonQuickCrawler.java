package thehackers.smartbuy.gui;

import java.io.IOException;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

public class AmazonQuickCrawler {
	private Document statsPage;
	
	AmazonQuickCrawler(String url, String user_agent) {
		try {
			this.statsPage = Jsoup.connect(url).timeout(30000).userAgent(user_agent).get();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public String getAvgStars() {
		String content = this.statsPage.select("span.a-size-base.a-color-secondary").text();
		return content;
	}
}
