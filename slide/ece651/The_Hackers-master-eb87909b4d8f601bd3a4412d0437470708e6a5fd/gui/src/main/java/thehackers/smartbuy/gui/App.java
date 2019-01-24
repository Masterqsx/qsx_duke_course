package thehackers.smartbuy.gui;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Random;

import com.ECS.client.jax.EditorialReview;
import com.ECS.client.jax.ImageSet;
import com.ECS.client.jax.Item;
import com.ECS.client.jax.Item.ImageSets;
import com.ECS.client.jax.ItemLookupResponse;
import com.ECS.client.jax.Items;
import com.ECS.client.jax.ItemSearchResponse;

import spark.ModelAndView;
import spark.template.velocity.VelocityTemplateEngine;

import static spark.Spark.*;

public class App {
	private static final String url_base = "http://www.amazon.com/gp/customer-reviews/widgets/average-customer-review/popover/ref=dpx_acr_pop_?contextId=dpx&asin=";
	private static ArrayList user_agent_list = new ArrayList();
	//the method it used to compute decrease/increase percentage
	private static String percentage(Float x, Float y){
		Float num = ((x-y) * 100)/y;
		String pert = Float.toString(num) +"%";
		return pert;
	}
	
	public static void main(String[] args) {
		
		// initialize user agents handler
		UserAgentsHandler agentsHandler = new UserAgentsHandler();
		staticFileLocation("/public");
		
		// initialize AWSRequst object
		AWSRequest requestObj = new AWSRequest();
			
		get("/", (request, response) -> {
            HashMap model = new HashMap();
            return new ModelAndView(model, "templates/frontpage.vtl");
          }, new VelocityTemplateEngine());
		
		get("/list", (request, response) -> {
            HashMap model = new HashMap();
            String AWSsort = "";
            String keyword = request.queryParams("keyword");
            String searchIndex = request.queryParams("category");
            String sortOption = request.queryParams("sort");
            if ( sortOption.equals("related") ) AWSsort = "relevancerank";
            else if ( sortOption.equals("highlow") ) AWSsort = "-price";
            else if  (sortOption.equals("lowhigh") ) AWSsort = "price";
            else if ( sortOption.equals("rating") ) AWSsort = "reviewrank";
                        
            int numOfReturnedPages = 2;
            ArrayList sbList = new ArrayList();
            for (int i = 1; i <= numOfReturnedPages; i++) {
	            // specify what Amazon API should return
	            requestObj.setRequest(searchIndex, keyword, "Images,ItemIds,ItemAttributes,OfferSummary", i, AWSsort);
	            // make a request and store the retrieved response
	            ItemSearchResponse result = requestObj.getResponse();
	            // for all the items returned in the response, get all relevant info
	            int j=0;
	            for (Items itemList : result.getItems()) {
	            	for (Item item : itemList.getItem()) {
	            		String title = "N/A";
	            		String lowestPrice = "N/A";
            			String imgURL = "https://upload.wikimedia.org/wikipedia/commons/thumb/a/ac/No_image_available.svg/300px-No_image_available.svg.png";
            			String asin = "N/A";
            			try {
            				title = item.getItemAttributes().getTitle();
	            		} catch (java.lang.NullPointerException e) {}
            			try {
            				lowestPrice = item.getOfferSummary().getLowestNewPrice().getFormattedPrice();
	            		} catch (java.lang.NullPointerException e) {}
            			try {
            				imgURL = item.getLargeImage().getURL();
	            		} catch (java.lang.NullPointerException e) {}
            			try {
            				asin = item.getASIN();
            			} catch (java.lang.NullPointerException e) {}
	                    AmazonQuickCrawler avg_stars_parser = new AmazonQuickCrawler( url_base + item.getASIN(), 
	                    		agentsHandler.getRandomAgent() );
	                    String avgRating = avg_stars_parser.getAvgStars().split(" ", 2)[0];

	            		SBItem sb = new SBItem(title, lowestPrice, imgURL, avgRating, asin);
	            		sbList.add(sb);
	            		j++;
	            	}
	            }
            }
            model.put("sbList", sbList);
            model.put("keyword", keyword);
            model.put("category", searchIndex);
            model.put("sortoption", sortOption);

            return new ModelAndView(model, "templates/list-page.vtl");
          }, new VelocityTemplateEngine());
		
		get("/detail", (request, response) -> {
            HashMap model = new HashMap();
            String asin = request.queryParams("id");
            String avgRating = request.queryParams("avgsr");
            
            ItemLookupResponse result = requestObj.getItemLookUp(asin);
            ArrayList imgList = new ArrayList();
            String title = "";
            String description = "";
            String iFrameURL = "";
            String lowestPrice = "N/A";
            String productURL = "";
            for (Items itemList : result.getItems()) {
            	for (Item item : itemList.getItem()) {
            		title = item.getItemAttributes().getTitle();
            		try {
            			iFrameURL = item.getCustomerReviews().getIFrameURL();
            		} catch (Exception e) {}
                    try {
                    	lowestPrice = item.getOfferSummary().getLowestNewPrice().getFormattedPrice();
                    } catch (Exception e) {}
                    try {
                    	productURL = item.getDetailPageURL();
                    } catch (Exception e) {}
                    try {
	                    for (EditorialReview edt : item.getEditorialReviews().getEditorialReview()) {
	                		description = edt.getContent();
	                	}
                    } catch (Exception e) {}

                    for (ImageSets img : item.getImageSets()) {
                    	for (ImageSet pic : img.getImageSet()) {
                    		try {
                    			imgList.add(pic.getLargeImage().getURL());
                    		} catch (Exception e) {}
                    	}
                    }

            	}
            }
            model.put("sbItem", new SBItem(title, lowestPrice, "", avgRating, asin));
            model.put("imgList", imgList);
            model.put("description", description);
            model.put("productURL", productURL);
            
            AmazonDetailCrawler azCrawler = new AmazonDetailCrawler(productURL, iFrameURL, 
            		agentsHandler.getRandomAgent(),
            		agentsHandler.getRandomAgent());
            model.put("mostUsefulRating", azCrawler.getMostUseFulRating());
            model.put("mostCurrentRating", azCrawler.getMostRecentRating());
            model.put("azCrawler", azCrawler);
            

            //use SimpleClient to get the price history chart
            SimpleClient client = new SimpleClient(0,"");
            client.reset(productURL);
    		client.run();
    		String priceChart = client.imageSrc.equals("no image")?
 		    	   "https://upload.wikimedia.org/wikipedia/commons/thumb/a/ac/No_image_available.svg/300px-No_image_available.svg.png":client.imageSrc;
    		model.put("priceChart", priceChart);
    		//use SimpleClient to get the price table
    		model.put("LowestPrice", client.pri.low_price);
    		model.put("LowestTime", client.pri.low_time);
    		model.put("HighestPrice", client.pri.high_price);
    		model.put("HighestTime", client.pri.high_time);
    		model.put("AveragePrice",client.pri.average);
    		model.put("CurrentPrice", lowestPrice);
    		
    		String compareHighestPrice = "";
    		String compareLowestPrice = "";
    		String compareAveragePrice = "";
    		try {
    			compareHighestPrice = percentage(Float.parseFloat(lowestPrice.substring(1)), Float.parseFloat(client.pri.high_price.substring(1)));
    		} catch (Exception e) {}
    		try {
    			compareLowestPrice = percentage(Float.parseFloat(lowestPrice.substring(1)), Float.parseFloat(client.pri.low_price.substring(1)));
    		} catch (Exception e) {}
    		try {
    			compareAveragePrice = percentage(Float.parseFloat(lowestPrice.substring(1)), Float.parseFloat(client.pri.average.substring(1)));
    		} catch (Exception e) {}
    		
    		model.put("compareHighestPrice", compareHighestPrice);
    		model.put("compareLowestPrice", compareLowestPrice);
    		model.put("compareAveragePrice", compareAveragePrice);
            
    		return new ModelAndView(model, "templates/detail-page.vtl");
          }, new VelocityTemplateEngine());
	    
	}
}