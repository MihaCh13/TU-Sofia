/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package simple_jpa;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author User
 */
@Entity
@Table(name = "coffees")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Coffees.findAll", query = "SELECT c FROM Coffees c"),
    @NamedQuery(name = "Coffees.findById", query = "SELECT c FROM Coffees c WHERE c.id = :id"),
    @NamedQuery(name = "Coffees.findByCofName", query = "SELECT c FROM Coffees c WHERE c.cofName = :cofName"),
    @NamedQuery(name = "Coffees.findBySupId", query = "SELECT c FROM Coffees c WHERE c.supId = :supId"),
    @NamedQuery(name = "Coffees.findByPrice", query = "SELECT c FROM Coffees c WHERE c.price = :price"),
    @NamedQuery(name = "Coffees.findBySales", query = "SELECT c FROM Coffees c WHERE c.sales = :sales"),
    @NamedQuery(name = "Coffees.findByTotal", query = "SELECT c FROM Coffees c WHERE c.total = :total")})
public class Coffees implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "ID")
    private Integer id;
    @Column(name = "COF_NAME")
    private String cofName;
    @Column(name = "SUP_ID")
    private Integer supId;
    // @Max(value=?)  @Min(value=?)//if you know range of your decimal fields consider using these annotations to enforce field validation
    @Column(name = "PRICE")
    private Float price;
    @Column(name = "SALES")
    private Integer sales;
    @Column(name = "TOTAL")
    private Integer total;

    public Coffees() {
    }

    public Coffees(Integer id) {
        this.id = id;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getCofName() {
        return cofName;
    }

    public void setCofName(String cofName) {
        this.cofName = cofName;
    }

    public Integer getSupId() {
        return supId;
    }

    public void setSupId(Integer supId) {
        this.supId = supId;
    }

    public Float getPrice() {
        return price;
    }

    public void setPrice(Float price) {
        this.price = price;
    }

    public Integer getSales() {
        return sales;
    }

    public void setSales(Integer sales) {
        this.sales = sales;
    }

    public Integer getTotal() {
        return total;
    }

    public void setTotal(Integer total) {
        this.total = total;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Coffees)) {
            return false;
        }
        Coffees other = (Coffees) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "simple_jpa.Coffees[ id=" + id + " ]";
    }
    
}
