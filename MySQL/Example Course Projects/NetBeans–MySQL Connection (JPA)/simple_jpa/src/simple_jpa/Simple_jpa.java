/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package simple_jpa;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.persistence.Query;

/**
 *
 * @author User
 */
public class Simple_jpa {
	private EntityManagerFactory emf;
	private EntityManager em;
	private String PERSISTENCE_UNIT_NAME = "simple_jpaPU";

	public void select() throws Exception {
	
		Query q = em.createQuery("select m from Coffees m");
		List<Coffees> res = q.getResultList();
		
		for (int i=0;i<res.size();i++) {
			Coffees temp = (Coffees) res.get(i);
			System.out.println(temp.getCofName()+'\t'+temp.getSupId()+'\t'+
					temp.getSales()+'\t'+temp.getPrice()+'\t'+temp.getTotal());
		}
		System.out.println();
	}
	
	public void update() {
		Query q = em.createQuery("update Coffees c set c.price=c.price*1.1 where c.price=7.99");
		em.getTransaction().begin();
		q.executeUpdate();
		em.getTransaction().commit();
//		em.getTransaction().rollback();
	}
	public void setPrice(double newPrice, double searchPrice) {
		em.getTransaction().begin();
		Query q = em.createQuery("update Coffees c set c.price=?3 where c.price between ?1 and ?2");
		q.setParameter(3, newPrice);
		q.setParameter(1, searchPrice-0.01);
		q.setParameter(2, searchPrice+0.01);
		q.executeUpdate(); // execute a JPA UPDATE/DELETE query
		em.getTransaction().commit();
	}
	private void initEntityManager() {
	     emf = Persistence.createEntityManagerFactory(PERSISTENCE_UNIT_NAME);
	     em = emf.createEntityManager();
	 }

	 private void closeEntityManager() {
	     em.close();
	     emf.close();
	 }
	 
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Simple_jpa test = new Simple_jpa();
		try {
			test.initEntityManager();
//			test.update();
			test.setPrice(7.99, 8.789);
			test.select();
			test.closeEntityManager();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
