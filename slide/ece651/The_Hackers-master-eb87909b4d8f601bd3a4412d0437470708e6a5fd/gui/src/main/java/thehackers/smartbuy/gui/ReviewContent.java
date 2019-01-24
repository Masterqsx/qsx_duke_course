package thehackers.smartbuy.gui;

public class ReviewContent {
	private String title;
	private String review;
	private float rating;
	
	ReviewContent(String title, String review, float rating) {
		this.title = title;
		this.review = review;
		this.rating = rating;
	}
	
	public String getTitle() {
		return this.title;
	}
	
	public String getReview() {
		return this.review;
	}
	
	public float getRating() {
		return this.rating;
	}
}
