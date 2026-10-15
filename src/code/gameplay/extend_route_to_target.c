/* SPAN 0x800DE664..0x800DEC04 */
/* LDSYM D_80135834=0x80135834 */
/* LDSYM func_800DE3EC=0x800DE3EC */
/* LDSYM func_800E09B0=0x800E09B0 */
/* LDSYM func_800E0A48=0x800E0A48 */
/* LDSYM func_800E0E84=0x800E0E84 */
/* LDSYM func_800E0EA8=0x800E0EA8 */
/* LDSYM func_800E18B0=0x800E18B0 */
/* LDSYM func_800E19DC=0x800E19DC */
#include "types.h"
typedef struct RouteQueue
{
  u16 *data;
  u16 head;
  u16 tail;
  u16 count;
  u16 free;
  u16 capacity;
  u8 valid;
} RouteQueue;
typedef struct TriangleTable
{
  u8 pad0[0xC];
  u8 *records;
} TriangleTable;
typedef struct TriangleVertexRef
{
  u16 id;
  u16 pad2;
} TriangleVertexRef;
extern TriangleTable *D_80135834;
extern TriangleVertexRef *func_800E09B0(u16 cell);
extern s32 func_800E0A48(u16 id);
extern u16 func_800DE3EC(RouteQueue *queue, s32 point);
extern u16 func_800E0E84(u16 edge);
extern s32 func_800E0EA8(s32 a, s32 b, s32 point);
extern void func_800E18B0(u16 edge, s32 *a, s32 *b);
extern u8 func_800E19DC(u16 cell);
inline static TriangleVertexRef *triangle_ref(TriangleVertexRef *base, u16 index) { return base + index; }
inline static s32 *edge_ref(s32 *base, u16 index) { u32 offset = index * 4; return (s32 *)(offset + (u32)base); }
inline static u16 queue_get(RouteQueue *queue, u16 index)
{
  if (index >= queue->count)
  {
    return 0;
  }
  return queue->data[(queue->head + index) % queue->capacity];
}

inline static u16 queue_last(RouteQueue *queue)
{
  if (queue->count == 0)
  {
    return 0;
  }
  return queue_get(queue, queue->count - 1);
}

inline static void queue_push(RouteQueue *queue, u16 value)
{
  u16 slot;
  if (queue->count < queue->capacity)
  {
    if ((queue->count + queue->free) == queue->capacity)
    {
      slot = queue->tail;
      queue->tail = (slot + 1) % queue->capacity;
      queue->free--;
    }
    else
    {
      slot = (queue->head + queue->count) % queue->capacity;
    }
    queue->data[slot] = value;
    queue->count++;
  }
}

u16 extend_route_to_target(RouteQueue *queue, s32 from, s32 to, u8 mask, s32 reset)
    __asm__("func_800DE664");

u16 extend_route_to_target(RouteQueue *queue, s32 from, s32 to, u8 mask, s32 reset)
{
  s32 edges[3];
  s32 a;
  s32 b;
  s32 pathClear;
  u16 result;
  u16 edge;
  u16 triangle;
  u16 attempts;
  u16 initialEdge;
  u16 i;
  unsigned initialClear;
  result = 0;
  initialEdge = queue_last(queue);
  triangle = initialEdge / 3;
  if (reset == 0)
  {
    TriangleVertexRef *initialVertices;
    u16 i;
    u32 blocked;
    initialVertices = func_800E09B0(triangle);
    blocked = 0;
    if (!(!(initialVertices == 0)))
    {
      initialClear = 0;
    }
    else
    {
      for (i = 0; i < 3; i++)
      {
        u16 first;
        u16 initialNext = (i + 1) % 3;
        u8 *records;
        first = triangle_ref(initialVertices, i)->id;
        records = D_80135834->records;
        { u16 second = triangle_ref(initialVertices, initialNext)->id;
        if (func_800E0EA8((s32) (records + (first * 8)), (s32) (records + (second * 8)), from) == 0)
        {
          blocked = 1;
        }
        }
      }

      initialClear = blocked < 1;
    }
    if (initialClear == 0)
    {
      triangle = func_800DE3EC(queue, from);
      if (initialClear < queue->count)
      {
        queue->count = 0;
        queue->valid = 1;
        for (i = 0; i < queue->count; i++)
        {
          {
            __typeof__(queue) ct25 = queue;
            if (func_800E19DC(queue_get(ct25, i) / 3))
            {
              queue->valid = 0;
            }
          }
        }

      }
    }
  }
  {
    TriangleVertexRef *triangleVertices = func_800E09B0(triangle);
    for (i = 0; i < 3; i++)
    {
      edges[i] = func_800E0EA8(from, func_800E0A48(triangle_ref(triangleVertices, i)->id), to);
    }

  }
  edge = 0;
  {
    for (i = 0; i < 3; i++)
    {
      u16 following = (i + 1) % 3;
      if ((*edge_ref(edges, i) != 0) && (*edge_ref(edges, following) == 0))
      {
        edge = i + (triangle * 3);
      }
    }

  }
  if (edge != 0)
  {
    goto follow_path;
  }
  return result;
  follow_path:
  {
    u16 next;
    attempts = 0;
    pathClear = func_800E19DC(edge / 3) == 0;
    do
    {
      u16 nextTriangle;
      u16 nextSide;
      queue_push(queue, edge);
      func_800E18B0(edge, &a, &b);
      if (func_800E0EA8(a, b, to) != 0)
      {
        result = edge / 3;
        goto done;
      }
      next = func_800E0E84(edge);
      if (next == 0)
      {
        goto done;
      }
      nextSide = (next + 2) % 3;
      nextTriangle = next / 3;
      {
        u8 status;
        status = func_800E19DC(nextTriangle);
        {
          __typeof__(status) ct95 = status;
          if (ct95 == 0)
          {
            pathClear = 1;
          }
          else
            if (pathClear != 0)
          {
            queue->valid = 0;
          }
        }
        if ((status & mask) != 0)
        {
          goto done;
        }
      }
      {
        TriangleVertexRef *nextVertices = func_800E09B0(nextTriangle);
        s32 mapped = func_800E0A48(triangle_ref(nextVertices, nextSide)->id);
        u16 triangleBase = nextTriangle * 3;
        if (func_800E0EA8(from, mapped, to) != 0)
        {
          edge = nextSide + triangleBase;
        }
        else
        {
          edge = triangleBase + ((nextSide + 2) % 3);
        }
      }
      attempts += 1;
    }
    while (attempts < 0xF8);
  }

  done:
  return result;

}

