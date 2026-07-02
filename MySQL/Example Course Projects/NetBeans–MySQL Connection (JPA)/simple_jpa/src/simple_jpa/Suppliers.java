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
@Table(name = "suppliers")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Suppliers.findAll", query = "SELECT s FROM Suppliers s"),
    @NamedQuery(name = "Suppliers.findBySupId", query = "SELECT s FROM Suppliers s WHERE s.supId = :supId"),
    @NamedQuery(name = "Suppliers.findBySupName", query = "SELECT s FROM Suppliers s WHERE s.supName = :supName"),
    @NamedQuery(name = "Suppliers.findByStreet", query = "SELECT s FROM Suppliers s WHERE s.street = :street"),
    @NamedQuery(name = "Suppliers.findByCity", query = "SELECT s FROM Suppliers s WHERE s.city = :city"),
    @NamedQuery(name = "Suppliers.findByState", query = "SELECT s FROM Suppliers s WHERE s.state = :state"),
    @NamedQuery(name = "Suppliers.findByZip", query = "SELECT s FROM Suppliers s WHERE s.zip = :zip")})
public class Suppliers implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "SUP_ID")
    private Integer supId;
    @Column(name = "SUP_NAME")
    private String supName;
    @Column(name = "STREET")
    private String street;
    @Column(name = "CITY")
    private String city;
    @Column(name = "STATE")
    private String state;
    @Column(name = "ZIP")
    private String zip;

    public Suppliers() {
    }

    public Suppliers(Integer supId) {
        this.supId = supId;
    }

    public Integer getSupId() {
        return supId;
    }

    public void setSupId(Integer supId) {
        this.supId = supId;
    }

    public String getSupName() {
        return supName;
    }

    public void setSupName(String supName) {
        this.supName = supName;
    }

    public String getStreet() {
        return street;
    }

    public void setStreet(String street) {
        this.street = street;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getState() {
        return state;
    }

    public void setState(String state) {
        this.state = state;
    }

    public String getZip() {
        return zip;
    }

    public void setZip(String zip) {
        this.zip = zip;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (supId != null ? supId.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Suppliers)) {
            return false;
        }
        Suppliers other = (Suppliers) object;
        if ((this.supId == null && other.supId != null) || (this.supId != null && !this.supId.equals(other.supId))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "simple_jpa.Suppliers[ supId=" + supId + " ]";
    }
    
}
