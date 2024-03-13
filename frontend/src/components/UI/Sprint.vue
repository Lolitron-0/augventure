<template>
  <div class="sprint">
    <div class="sprint-bar" :class="{ 'sprint-bar-voting': state === 'voting', 'sprint-bar-ended': state === 'ended' }"></div>
    <div class="sprint-circle" :class="{ 'sprint-circle-voting': state === 'voting', 'sprint-circle-ended': state === 'ended' }"></div>
  </div>
</template>

<script>

export default {
  props: {
    state: String
  }
}
</script>

<style scoped>
.sprint {
  display: flex;
  align-items: center;
  flex-direction: column;
  border: 1px solid red;
}

.sprint-bar {
  width: 4px;
  height: 100px;
  background-color: #ccc;
  //margin-right: 10px;
}

.sprint-bar-voting {
  background-color: #ffc107; /* Цвет для состояния "voting" */
}

.sprint-bar-ended {
  background-color: #28a745; /* Цвет для состояния "ended" */
}

.sprint-circle {
  width: 70px;
  height: 70px;
  border-radius: 50%;
  background-color: #ccc;
}

.sprint-circle-voting {
  background-color: #ffc107; /* Цвет для состояния "voting" */
}

.sprint-circle-ended {
  background-color: #28a745; /* Цвет для состояния "ended" */
}
</style>