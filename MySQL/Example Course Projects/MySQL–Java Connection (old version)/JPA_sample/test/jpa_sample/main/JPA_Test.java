package jpa_sample.main;

import java.util.List;
import jpa_sample.model.*;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.persistence.Query;

public class JPA_Test {

	private EntityManagerFactory emf;
	private EntityManager em;
	private String PERSISTENCE_UNIT_NAME = "JPA_sample";

	public void select() throws Exception {
	
		Query q = em.createQuery("select m from Coffee m");
		List<Coffee> res = q.getResultList();
		
		for (int i=0;i<res.size();i++) {
			Coffee temp = (Coffee) res.get(i);
			System.out.println(temp.getCofName()+'\t'+temp.getSupId()+'\t'+
					temp.getSales()+'\t'+temp.getPrice()+'\t'+temp.getTotal());
		}
		System.out.println();
	}
	
	public void update() {
		Query q = em.createQuery("update Coffee c set c.price=c.price*1.1 where c.price=7.99");
		em.getTransaction().begin();
		q.executeUpdate();
		em.getTransaction().commit();
//		em.getTransaction().rollback();
	}
	public void setPrice(double newPrice, double searchPrice) {
		em.getTransaction().begin();
		Query q = em.createQuery("update Coffee c set c.price=:newPrice where c.price between ?1 and ?2");
		q.setParameter("newPrice", newPrice);
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
		JPA_Test test = new JPA_Test();
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
