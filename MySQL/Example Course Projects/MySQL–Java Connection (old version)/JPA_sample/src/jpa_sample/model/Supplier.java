package jpa_sample.model;

import java.io.Serializable;
import javax.persistence.*;


/**
 * The persistent class for the suppliers database table.
 * 
 */
@Entity
@Table(name="suppliers")
public class Supplier implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	@Column(name="sup_id")
	private int supId;

	private String city;

	private String state;

	private String street;

	@Column(name="sup_name")
	private String supName;

	private String zip;

    public Supplier() {
    }

	public int getSupId() {
		return this.supId;
	}

	public void setSupId(int supId) {
		this.supId = supId;
	}

	public String getCity() {
		return this.city;
	}

	public void setCity(String city) {
		this.city = city;
	}

	public String getState() {
		return this.state;
	}

	public void setState(String state) {
		this.state = state;
	}

	public String getStreet() {
		return this.street;
	}

	public void setStreet(String street) {
		this.street = street;
	}

	public String getSupName() {
		return this.supName;
	}

	public void setSupName(String supName) {
		this.supName = supName;
	}

	public String getZip() {
		return this.zip;
	}

	public void setZip(String zip) {
		this.zip = zip;
	}

}