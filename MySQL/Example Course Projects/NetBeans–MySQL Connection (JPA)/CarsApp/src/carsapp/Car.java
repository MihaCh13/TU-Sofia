/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package carsapp;

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
@Table(name = "car")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Car.findAll", query = "SELECT c FROM Car c"),
    @NamedQuery(name = "Car.findByMake", query = "SELECT c FROM Car c WHERE c.make = :make"),
    @NamedQuery(name = "Car.findByModel", query = "SELECT c FROM Car c WHERE c.model = :model"),
    @NamedQuery(name = "Car.findByPrice", query = "SELECT c FROM Car c WHERE c.price = :price"),
    @NamedQuery(name = "Car.findByBodyStyle", query = "SELECT c FROM Car c WHERE c.bodyStyle = :bodyStyle"),
    @NamedQuery(name = "Car.findByColor", query = "SELECT c FROM Car c WHERE c.color = :color"),
    @NamedQuery(name = "Car.findBySunRoof", query = "SELECT c FROM Car c WHERE c.sunRoof = :sunRoof"),
    @NamedQuery(name = "Car.findBySpoiler", query = "SELECT c FROM Car c WHERE c.spoiler = :spoiler"),
    @NamedQuery(name = "Car.findByTireSize", query = "SELECT c FROM Car c WHERE c.tireSize = :tireSize"),
    @NamedQuery(name = "Car.findByTireType", query = "SELECT c FROM Car c WHERE c.tireType = :tireType"),
    @NamedQuery(name = "Car.findByModernness", query = "SELECT c FROM Car c WHERE c.modernness = :modernness")})
public class Car implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @Column(name = "MAKE")
    private String make;
    @Column(name = "MODEL")
    private String model;
    @Column(name = "PRICE")
    private Integer price;
    @Column(name = "BODY_STYLE")
    private String bodyStyle;
    @Column(name = "COLOR")
    private String color;
    @Column(name = "SUN_ROOF")
    private Integer sunRoof;
    @Column(name = "SPOILER")
    private Integer spoiler;
    @Column(name = "TIRE_SIZE")
    private Integer tireSize;
    @Column(name = "TIRE_TYPE")
    private Integer tireType;
    @Column(name = "MODERNNESS")
    private Integer modernness;

    public Car() {
    }

    public Car(String make) {
        this.make = make;
    }

    public String getMake() {
        return make;
    }

    public void setMake(String make) {
        this.make = make;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public Integer getPrice() {
        return price;
    }

    public void setPrice(Integer price) {
        this.price = price;
    }

    public String getBodyStyle() {
        return bodyStyle;
    }

    public void setBodyStyle(String bodyStyle) {
        this.bodyStyle = bodyStyle;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public Integer getSunRoof() {
        return sunRoof;
    }

    public void setSunRoof(Integer sunRoof) {
        this.sunRoof = sunRoof;
    }

    public Integer getSpoiler() {
        return spoiler;
    }

    public void setSpoiler(Integer spoiler) {
        this.spoiler = spoiler;
    }

    public Integer getTireSize() {
        return tireSize;
    }

    public void setTireSize(Integer tireSize) {
        this.tireSize = tireSize;
    }

    public Integer getTireType() {
        return tireType;
    }

    public void setTireType(Integer tireType) {
        this.tireType = tireType;
    }

    public Integer getModernness() {
        return modernness;
    }

    public void setModernness(Integer modernness) {
        this.modernness = modernness;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (make != null ? make.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Car)) {
            return false;
        }
        Car other = (Car) object;
        if ((this.make == null && other.make != null) || (this.make != null && !this.make.equals(other.make))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "carsapp.Car[ make=" + make + " ]";
    }
    
}
