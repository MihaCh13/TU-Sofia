'use client';

import { useState, useEffect } from 'react';
import {
  Dialog,
  DialogContent,
  DialogHeader,
  DialogTitle,
} from '@/components/ui/dialog';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from '@/components/ui/select';
import { useScheduleStore } from '@/lib/schedule-store';
import { DAYS, TIME_SLOTS, EVENT_TYPES, WEEK_TYPES } from '@/lib/schedule-types';
import type { ScheduleEvent, EventType, WeekType } from '@/lib/schedule-types';
import { Trash2 } from 'lucide-react';

interface EventModalProps {
  isOpen: boolean;
  onClose: () => void;
  event: ScheduleEvent | null;
  defaultDay?: string;
  defaultStartTime?: string;
}

export function EventModal({
  isOpen,
  onClose,
  event,
  defaultDay = '',
  defaultStartTime = '',
}: EventModalProps) {
  const { addEvent, updateEvent, deleteEvent } = useScheduleStore();

  const [formData, setFormData] = useState({
    title: '',
    professor: '',
    room: '',
    day: defaultDay || DAYS[0],
    startTime: defaultStartTime || '08:00',
    endTime: '10:00',
    type: 'lecture' as EventType,
    weekType: 'all' as WeekType,
    credits: 0,
  });

  useEffect(() => {
    if (event) {
      setFormData({
        title: event.title,
        professor: event.professor,
        room: event.room,
        day: event.day,
        startTime: event.startTime,
        endTime: event.endTime,
        type: event.type,
        weekType: event.weekType,
        credits: event.credits || 0,
      });
    } else {
      setFormData({
        title: '',
        professor: '',
        room: '',
        day: defaultDay || DAYS[0],
        startTime: defaultStartTime || '08:00',
        endTime: '10:00',
        type: 'lecture',
        weekType: 'all',
        credits: 0,
      });
    }
  }, [event, defaultDay, defaultStartTime, isOpen]);

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    
    if (event) {
      updateEvent(event.id, formData);
    } else {
      addEvent({
        id: Date.now().toString(),
        ...formData,
      });
    }
    onClose();
  };

  const handleDelete = () => {
    if (event) {
      deleteEvent(event.id);
      onClose();
    }
  };

  return (
    <Dialog open={isOpen} onOpenChange={onClose}>
      <DialogContent className="sm:max-w-[500px]">
        <DialogHeader>
          <DialogTitle>
            {event ? 'Редактиране на занятие' : 'Ново занятие'}
          </DialogTitle>
        </DialogHeader>
        <form onSubmit={handleSubmit} className="space-y-4">
          <div className="space-y-2">
            <Label htmlFor="title">Предмет</Label>
            <Input
              id="title"
              value={formData.title}
              onChange={(e) => setFormData({ ...formData, title: e.target.value })}
              placeholder="Въведете име на предмета"
              required
            />
          </div>

          <div className="grid grid-cols-2 gap-4">
            <div className="space-y-2">
              <Label htmlFor="professor">Преподавател</Label>
              <Input
                id="professor"
                value={formData.professor}
                onChange={(e) => setFormData({ ...formData, professor: e.target.value })}
                placeholder="Име на преподавател"
              />
            </div>
            <div className="space-y-2">
              <Label htmlFor="room">Зала</Label>
              <Input
                id="room"
                value={formData.room}
                onChange={(e) => setFormData({ ...formData, room: e.target.value })}
                placeholder="Номер на зала"
              />
            </div>
          </div>

          <div className="grid grid-cols-3 gap-4">
            <div className="space-y-2">
              <Label>Ден</Label>
              <Select
                value={formData.day}
                onValueChange={(value) => setFormData({ ...formData, day: value })}
              >
                <SelectTrigger>
                  <SelectValue />
                </SelectTrigger>
                <SelectContent>
                  {DAYS.map((day) => (
                    <SelectItem key={day} value={day}>
                      {day}
                    </SelectItem>
                  ))}
                </SelectContent>
              </Select>
            </div>
            <div className="space-y-2">
              <Label>Начало</Label>
              <Select
                value={formData.startTime}
                onValueChange={(value) => setFormData({ ...formData, startTime: value })}
              >
                <SelectTrigger>
                  <SelectValue />
                </SelectTrigger>
                <SelectContent>
                  {TIME_SLOTS.map((time) => (
                    <SelectItem key={time} value={time}>
                      {time}
                    </SelectItem>
                  ))}
                </SelectContent>
              </Select>
            </div>
            <div className="space-y-2">
              <Label>Край</Label>
              <Select
                value={formData.endTime}
                onValueChange={(value) => setFormData({ ...formData, endTime: value })}
              >
                <SelectTrigger>
                  <SelectValue />
                </SelectTrigger>
                <SelectContent>
                  {TIME_SLOTS.map((time) => (
                    <SelectItem key={time} value={time}>
                      {time}
                    </SelectItem>
                  ))}
                </SelectContent>
              </Select>
            </div>
          </div>

          <div className="grid grid-cols-2 gap-4">
            <div className="space-y-2">
              <Label>Тип занятие</Label>
              <Select
                value={formData.type}
                onValueChange={(value: EventType) => setFormData({ ...formData, type: value })}
              >
                <SelectTrigger>
                  <SelectValue />
                </SelectTrigger>
                <SelectContent>
                  {Object.entries(EVENT_TYPES).map(([key, { label }]) => (
                    <SelectItem key={key} value={key}>
                      {label}
                    </SelectItem>
                  ))}
                </SelectContent>
              </Select>
            </div>
            <div className="space-y-2">
              <Label>Седмица</Label>
              <Select
                value={formData.weekType}
                onValueChange={(value: WeekType) => setFormData({ ...formData, weekType: value })}
              >
                <SelectTrigger>
                  <SelectValue />
                </SelectTrigger>
                <SelectContent>
                  {Object.entries(WEEK_TYPES).map(([key, label]) => (
                    <SelectItem key={key} value={key}>
                      {label}
                    </SelectItem>
                  ))}
                </SelectContent>
              </Select>
            </div>
          </div>

          <div className="flex justify-between pt-4">
            {event && (
              <Button type="button" variant="destructive" onClick={handleDelete} className="gap-2">
                <Trash2 className="w-4 h-4" />
                Изтрий
              </Button>
            )}
            <div className="flex gap-2 ml-auto">
              <Button type="button" variant="outline" onClick={onClose}>
                Отказ
              </Button>
              <Button type="submit">
                {event ? 'Запази' : 'Добави'}
              </Button>
            </div>
          </div>
        </form>
      </DialogContent>
    </Dialog>
  );
}
