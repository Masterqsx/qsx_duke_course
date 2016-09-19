package thehackers.smartbuy.gui;

public class SBItem {
	private String title;
	private String lowestNewPrice;
	private String primImageURL;
	private float avgRating = 0;
	private String asin;
	
	SBItem(String title, String lowestNewPrice, String primImageURL, String avgRating, String asin) {
		this.title = title;
		this.lowestNewPrice = lowestNewPrice;
		this.primImageURL = primImageURL;
		try {
			this.avgRating = Float.parseFloat(avgRating);
		} catch (java.lang.NumberFormatException e) {}
		this.asin = asin;
	}
	
	public String getTitle() {
		return this.title;
	}
	
	public String getLowestNewPrice() {
		return this.lowestNewPrice;
	}
	
	public String getPrimImageURL() {
		return this.primImageURL;
	}
	
	public float getAvgRating() {
		return this.avgRating;
	}
	
	public String getAsin() {
		return this.asin;
	}
}