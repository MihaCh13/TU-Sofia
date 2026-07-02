package jpa_sample.model;

import java.io.Serializable;
import javax.persistence.*;

import static javax.persistence.FetchType.EAGER;
import static javax.persistence.FetchType.LAZY;


/**
 * The persistent class for the coffees database table.
 * 
 */
@Entity
@Table(name="coffees")
public class Coffee implements Serializable {
	private static final long serialVersionUID = 1L;

	@Id
	@Column(name="cof_name")
	private String cofName;

	private double price;

	private int sales;

	@Column(name="sup_id")
	private int supId;

	private int total;

    public Coffee() {
    }

	public String getCofName() {
		return this.cofName;
	}

	public void setCofName(String cofName) {
		this.cofName = cofName;
	}

	public double getPrice() {
		return this.price;
	}

	public void setPrice(double price) {
		this.price = price;
	}

	public int getSales() {
		return this.sales;
	}

	public void setSales(int sales) {
		this.sales = sales;
	}

	public int getSupId() {
		return this.supId;
	}

	public void setSupId(int supId) {
		this.supId = supId;
	}

	public int getTotal() {
		return this.total;
	}

	public void setTotal(int total) {
		this.total = total;
	}

}