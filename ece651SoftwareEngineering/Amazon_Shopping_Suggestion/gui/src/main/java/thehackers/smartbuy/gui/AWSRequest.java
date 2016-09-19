package thehackers.smartbuy.gui;

import java.math.BigInteger;

import com.ECS.client.jax.ItemLookupResponse;
import com.ECS.client.jax.ItemSearchResponse;

public class AWSRequest {
	/* 
	 * AWSRequest class creates a simple request to 
	 * Product Advertising Amazon API 
	 * and returns an item search response.
	 */
	private String awsKey;
	private String secretKey;
	private String associateTag;
	private final com.ECS.client.jax.AWSECommerceService service;
	private final com.ECS.client.jax.AWSECommerceServicePortType port;
	private final com.ECS.client.jax.ItemSearchRequest itemRequest;
	private com.ECS.client.jax.ItemLookupRequest itemLookUp;
	
	AWSRequest(String awsKey, String associateTag, String secretKey) {
		this.awsKey = awsKey;
		this.secretKey = secretKey;
		this.associateTag = associateTag;
		
		// Set the service
		this.service = new com.ECS.client.jax.AWSECommerceService();
		this.service.setHandlerResolver(new AwsHandlerResolver(this.secretKey));
		
		// Set the service port
		this.port = service.getAWSECommerceServicePort();
			
		// Get the operation object
		this.itemRequest = new com.ECS.client.jax.ItemSearchRequest();	
		this.itemLookUp = new com.ECS.client.jax.ItemLookupRequest();
	}
	
	AWSRequest() {
		this("AKIAI3OXGOGWKURY554Q", "smartbuy002-20", 
				"hFLoFXMknOAgLsj7Mc0GWqiR9VOfXJQoItcqtxlC");
	}
	
	public void setRequest(String searchIndex, String keywords, String responseGroups, int page, String sortOption) {
		// Fill in the request object
		this.itemRequest.setSearchIndex(searchIndex);
		this.itemRequest.setKeywords(keywords);
		this.itemRequest.setItemPage(BigInteger.valueOf(page));
		this.itemRequest.setCondition("New");
		this.itemRequest.setSort(sortOption);
		/*
		 *  Specify the types of values to return
		 *  Multiple response groups separated by commas
		 *  i.e. ItemAttributes,Reviews,Images,Offers
		 */
		this.itemRequest.getResponseGroup().add(responseGroups);
	}
	
	public ItemSearchResponse getResponse() {
		/*
		 * Attempts to make a request to Amazon server
		 * Success: response returned
		 * Failure: returns null
		 */
		com.ECS.client.jax.ItemSearch ItemElement= new com.ECS.client.jax.ItemSearch();
		ItemElement.setAWSAccessKeyId(this.awsKey);
		ItemElement.setAssociateTag(this.associateTag);
		ItemElement.getRequest().add(this.itemRequest);
		
		// Call the Web service operation
		// and store the response in the response object
		try {
			com.ECS.client.jax.ItemSearchResponse response = port.itemSearch(ItemElement);
			return response;
		} catch (Exception e) {
			System.out.println("Error Response: " + e);
			return null;
		}
	}
	
	public ItemLookupResponse getItemLookUp(String asin) {
		this.itemLookUp = new com.ECS.client.jax.ItemLookupRequest();
		this.itemLookUp.getItemId().add(asin);
		this.itemLookUp.setTruncateReviewsAt(BigInteger.valueOf(99999));
		this.itemLookUp.getResponseGroup().add("EditorialReview,Reviews,Images,OfferSummary,ItemAttributes");
		com.ECS.client.jax.ItemLookup ItemElement= new com.ECS.client.jax.ItemLookup();
		ItemElement.setAWSAccessKeyId(this.awsKey);
		ItemElement.setAssociateTag(this.associateTag);
		ItemElement.getRequest().add(this.itemLookUp);
		
		try {
			com.ECS.client.jax.ItemLookupResponse response = port.itemLookup(ItemElement);
			return response;
		} catch (Exception e) {
			System.out.println("Error Response: " + e);
			return null;
		}
	}
	
	public void setItemPage(int page) {
		this.itemRequest.setItemPage(BigInteger.valueOf(page));
	}
	
	public void setAWSKey(String awskey) {
		this.awsKey = awskey;
	}
	
	public void setSecretKey(String secretKey) {
		this.secretKey = secretKey;
	}
	
	public void setAssociateTag(String associateTag) {
		this.associateTag = associateTag;
	}
}
