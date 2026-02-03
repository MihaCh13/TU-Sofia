'use client';

import { useState } from 'react';
import { ScheduleTable } from '@/components/schedule/schedule-table';
import { EventModal } from '@/components/schedule/event-modal';
import { Header } from '@/components/schedule/header';
import { Sidebar } from '@/components/schedule/sidebar';
import type { ScheduleEvent } from '@/lib/schedule-types';

export default function Page() {
  const [isModalOpen, setIsModalOpen] = useState(false);
  const [editingEvent, setEditingEvent] = useState<ScheduleEvent | null>(null);
  const [selectedDay, setSelectedDay] = useState('');
  const [selectedStartTime, setSelectedStartTime] = useState('');
  const [selectedEndTime, setSelectedEndTime] = useState('');

  const handleAddEvent = () => {
    setEditingEvent(null);
    setSelectedDay('');
    setSelectedStartTime('');
    setSelectedEndTime('');
    setIsModalOpen(true);
  };

  const handleCellClick = (day: string, startTime: string, endTime: string) => {
    setSelectedDay(day);
    setSelectedStartTime(startTime);
    setSelectedEndTime(endTime);
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

  return (
    <div className="flex h-screen bg-background">
      <Sidebar />
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
        editingEvent={editingEvent}
        defaultDay={selectedDay}
        defaultStartTime={selectedStartTime}
        defaultEndTime={selectedEndTime}
      />
    </div>
  );
}
