'use client';

import { useState, useEffect } from 'react';
import { Button } from '@/components/ui/button';
import {
  Dialog,
  DialogContent,
  DialogHeader,
  DialogTitle,
  DialogFooter,
} from '@/components/ui/dialog';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from '@/components/ui/select';
import { DAYS, DAY_NAMES, TIME_SLOTS, COLOR_OPTIONS } from '@/lib/schedule-types';
import type { ScheduleEvent } from '@/lib/schedule-types';
import { useScheduleStore } from '@/lib/schedule-store';
import { Trash2 } from 'lucide-react';

interface EventModalProps {
  isOpen: boolean;
  onClose: () => void;
  editingEvent: ScheduleEvent | null;
  defaultDay?: string;
  defaultStartTime?: string;
  defaultEndTime?: string;
}

export function EventModal({
  isOpen,
  onClose,
  editingEvent,
  defaultDay = '',
  defaultStartTime = '',
  defaultEndTime = '',
}: EventModalProps) {
  const [title, setTitle] = useState('');
  const [professor, setProfessor] = useState('');
  const [room, setRoom] = useState('');
  const [day, setDay] = useState('');
  const [startTime, setStartTime] = useState('');
  const [endTime, setEndTime] = useState('');
  const [color, setColor] = useState(COLOR_OPTIONS[0]);
  const [credits, setCredits] = useState('');

  const { addEvent, updateEvent, deleteEvent } = useScheduleStore();

  useEffect(() => {
    if (editingEvent) {
      setTitle(editingEvent.title);
      setProfessor(editingEvent.professor);
      setRoom(editingEvent.room);
      setDay(editingEvent.day);
      setStartTime(editingEvent.start_time);
      setEndTime(editingEvent.end_time);
      setColor(editingEvent.color || COLOR_OPTIONS[0]);
      setCredits(editingEvent.credits?.toString() || '');
    } else {
      setTitle('');
      setProfessor('');
      setRoom('');
      setDay(defaultDay);
      setStartTime(defaultStartTime);
      setEndTime(defaultEndTime);
      setColor(COLOR_OPTIONS[0]);
      setCredits('');
    }
  }, [isOpen, editingEvent, defaultDay, defaultStartTime, defaultEndTime]);

  const handleSave = () => {
    if (!title || !day || !startTime || !endTime) {
      alert('Please fill in all required fields');
      return;
    }

    if (editingEvent) {
      updateEvent(editingEvent.id, {
        title,
        professor,
        room,
        day,
        start_time: startTime,
        end_time: endTime,
        color,
        credits: credits ? parseInt(credits) : undefined,
      });
    } else {
      const newEvent: ScheduleEvent = {
        id: Date.now().toString(),
        title,
        professor,
        room,
        day,
        start_time: startTime,
        end_time: endTime,
        color,
        credits: credits ? parseInt(credits) : undefined,
      };
      addEvent(newEvent);
    }

    onClose();
  };

  const handleDelete = () => {
    if (editingEvent && confirm('Are you sure you want to delete this class?')) {
      deleteEvent(editingEvent.id);
      onClose();
    }
  };

  const availableEndTimes = TIME_SLOTS.filter((slot) => {
    if (!startTime) return false;
    const startIdx = TIME_SLOTS.findIndex((s) => s.start === startTime);
    const currentIdx = TIME_SLOTS.findIndex((s) => s.start === slot.start);
    return currentIdx > startIdx && !slot.lunch;
  }).map((slot) => slot.end);

  return (
    <Dialog open={isOpen} onOpenChange={onClose}>
      <DialogContent className="sm:max-w-[500px]">
        <DialogHeader>
          <DialogTitle>{editingEvent ? 'Edit Class' : 'Add New Class'}</DialogTitle>
        </DialogHeader>

        <div className="space-y-4">
          <div className="space-y-2">
            <Label htmlFor="title">Class Title *</Label>
            <Input
              id="title"
              placeholder="e.g., Mathematics 101"
              value={title}
              onChange={(e) => setTitle(e.target.value)}
            />
          </div>

          <div className="space-y-2">
            <Label htmlFor="professor">Professor</Label>
            <Input
              id="professor"
              placeholder="e.g., Prof. John Doe"
              value={professor}
              onChange={(e) => setProfessor(e.target.value)}
            />
          </div>

          <div className="space-y-2">
            <Label htmlFor="room">Room/Location</Label>
            <Input
              id="room"
              placeholder="e.g., Room 101"
              value={room}
              onChange={(e) => setRoom(e.target.value)}
            />
          </div>

          <div className="grid grid-cols-2 gap-4">
            <div className="space-y-2">
              <Label htmlFor="day">Day *</Label>
              <Select value={day} onValueChange={setDay}>
                <SelectTrigger id="day">
                  <SelectValue placeholder="Select day" />
                </SelectTrigger>
                <SelectContent>
                  {DAYS.map((d) => (
                    <SelectItem key={d} value={d}>
                      {DAY_NAMES[d]}
                    </SelectItem>
                  ))}
                </SelectContent>
              </Select>
            </div>

            <div className="space-y-2">
              <Label htmlFor="credits">Credits</Label>
              <Input
                id="credits"
                type="number"
                placeholder="e.g., 6"
                value={credits}
                onChange={(e) => setCredits(e.target.value)}
              />
            </div>
          </div>

          <div className="grid grid-cols-2 gap-4">
            <div className="space-y-2">
              <Label htmlFor="startTime">Start Time *</Label>
              <Select value={startTime} onValueChange={setStartTime}>
                <SelectTrigger id="startTime">
                  <SelectValue placeholder="Select start time" />
                </SelectTrigger>
                <SelectContent>
                  {TIME_SLOTS.filter((slot) => !slot.lunch).map((slot) => (
                    <SelectItem key={slot.start} value={slot.start}>
                      {slot.start}
                    </SelectItem>
                  ))}
                </SelectContent>
              </Select>
            </div>

            <div className="space-y-2">
              <Label htmlFor="endTime">End Time *</Label>
              <Select value={endTime} onValueChange={setEndTime}>
                <SelectTrigger id="endTime">
                  <SelectValue placeholder="Select end time" />
                </SelectTrigger>
                <SelectContent>
                  {availableEndTimes.length > 0 ? (
                    availableEndTimes.map((time) => (
                      <SelectItem key={time} value={time}>
                        {time}
                      </SelectItem>
                    ))
                  ) : (
                    <SelectItem value="" disabled>
                      Select start time first
                    </SelectItem>
                  )}
                </SelectContent>
              </Select>
            </div>
          </div>

          <div className="space-y-2">
            <Label>Color</Label>
            <div className="flex gap-2 flex-wrap">
              {COLOR_OPTIONS.map((colorOption) => (
                <button
                  key={colorOption}
                  className={`w-10 h-10 rounded-lg border-2 transition-all ${
                    color === colorOption
                      ? 'border-foreground scale-110'
                      : 'border-transparent hover:scale-105'
                  }`}
                  style={{ backgroundColor: colorOption }}
                  onClick={() => setColor(colorOption)}
                  aria-label={`Select color ${colorOption}`}
                />
              ))}
            </div>
          </div>
        </div>

        <DialogFooter className="flex gap-2 justify-between">
          {editingEvent && (
            <Button
              variant="destructive"
              onClick={handleDelete}
              className="mr-auto"
            >
              <Trash2 className="w-4 h-4 mr-2" />
              Delete
            </Button>
          )}
          <div className="flex gap-2">
            <Button variant="outline" onClick={onClose}>
              Cancel
            </Button>
            <Button onClick={handleSave}>
              {editingEvent ? 'Update' : 'Add'} Class
            </Button>
          </div>
        </DialogFooter>
      </DialogContent>
    </Dialog>
  );
}
