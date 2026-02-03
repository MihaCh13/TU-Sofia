'use client';

import { useState, useEffect } from 'react';
import { ScheduleTable } from '@/components/schedule/schedule-table';
import { EventModal } from '@/components/schedule/event-modal';
import { Header } from '@/components/schedule/header';
import { useScheduleStore } from '@/lib/schedule-store';
import type { ScheduleEvent } from '@/lib/schedule-types';

export default function Page() {
  const [isModalOpen, setIsModalOpen] = useState(false);
  const [editingEvent, setEditingEvent] = useState<ScheduleEvent | null>(null);
  const [selectedDay, setSelectedDay] = useState('');
  const [selectedStartTime, setSelectedStartTime] = useState('');
  const [mounted, setMounted] = useState(false);

  useEffect(() => {
    useScheduleStore.persist.rehydrate();
    setMounted(true);
  }, []);

  const handleAddEvent = () => {
    setEditingEvent(null);
    setSelectedDay('');
    setSelectedStartTime('');
    setIsModalOpen(true);
  };

  const handleCellClick = (day: string, startTime: string) => {
    setSelectedDay(day);
    setSelectedStartTime(startTime);
    setEditingEvent(null);
    setIsModalOpen(true);
  };

  const handleEventClick = (event: ScheduleEvent) => {
    setEditingEvent(event);
    setIsModalOpen(true);
  };

  const handleCloseModal = () => {
    setIsModalOpen(false);
    setEditingEvent(null);
  };

  if (!mounted) {
    return <div className="flex items-center justify-center h-screen">Зареждане...</div>;
  }

  return (
    <div className="flex h-screen bg-background">
      <div className="flex-1 flex flex-col overflow-hidden">
        <Header onAddEvent={handleAddEvent} />
        <ScheduleTable
          onCellClick={handleCellClick}
          onEventClick={handleEventClick}
        />
      </div>
      <EventModal
        isOpen={isModalOpen}
        onClose={handleCloseModal}
        event={editingEvent}
        defaultDay={selectedDay}
        defaultStartTime={selectedStartTime}
      />
    </div>
  );
}
