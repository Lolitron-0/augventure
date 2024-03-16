<template>
  <div class="block_for_sprint_and_time">
    <div class="sprint">
      <div class="sprint-circle" :class="{ 'sprint-circle-voting': state === 'voting', 'sprint-circle-ended': state === 'ended' }"></div>
      <div class="sprint-bar"></div>
    </div>
    <div class="time">
      {{ data }}
    </div>
  </div>
</template>

<script>

export default {
  props: {
    state: String,
    data: String,
  },
}
</script>

<style scoped>
.block_for_sprint_and_time {
  bottom: 0;
  width: 100%;
  display: flex;
  flex-direction: row;
  //border: 1px solid green;
}

.sprint {
  width: 70%;
  bottom: 0;
  display: flex;
  align-items: center;
  flex-direction: column;
  //border: 1px solid red;
}

.sprint-bar {
  left: 40px;
  width: 4px;
  height: 100px;
  background-color: var(--message-green-color);
  //margin-right: 10px;
}

.sprint-circle {
  left: 40px;
  width: 60px;
  height: 60px;
  border-radius: 50%;
  cursor: pointer;
  //background-color: var(--background-app-color);
  //border: 7px solid var(--background-btn-color);
}

.sprint-circle-voting {
  background-color: var(--message-green-color);
  border: 0;
}

.sprint-circle-ended {
  background-color: var(--background-app-color);
  border: 7px solid var(--message-green-color);
}

.time {
  color: var(--text-wight-color);
}
</style>